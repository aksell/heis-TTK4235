#include "fsm.h"

bool fsm_init(){
	elev_set_motor_direction(DIRN_UP);
    while(elev_get_floor_sensor_signal()==-1){};
    elev_set_motor_direction(DIRN_STOP);
    current_state = IDLE;
    return 1;
}

void fsm_ev_floor_sensor(int floor){
	elev_set_floor_indicator(floor);
	current_floor = floor;

	switch (current_state){

		case IDLE:
			break;
		case MOVING:
			if(order_should_stop(floor, motor_dir)){
				current_state = STOP;
			}
			break;
		case STOP:
			motor_dir = DIRN_STOP;
			elev_set_motor_direction(DIRN_STOP);

			if(!timer_active()){
				timer_set();
			}

			elev_set_door_open_lamp(ON);
			order_completed(floor);
			fsm_clear_lights(current_floor);

			if(timer_get() > WAIT_TIME){
				timer_reset();
				elev_set_door_open_lamp(OFF);

				if(orders_none()){
					current_state = IDLE;
				}else{
					motor_dir = order_get_dir(current_floor);
					elev_set_motor_direction(motor_dir);
					current_state=MOVING;
					real_floor = current_floor + motor_dir/2.0;
				}
			}
			break;
		case EMERGENCY:
			elev_set_door_open_lamp(ON);
			while(elev_get_stop_signal()){};
			elev_set_stop_lamp(OFF);
			elev_set_door_open_lamp(OFF);
			current_state = STOP;
			break;

		}


}


void fsm_ev_emergency(){
	elev_set_motor_direction(DIRN_STOP);
	motor_dir = DIRN_STOP;
	order_clear();
	//clear order + request lights
	for(int f = 0; f<N_FLOORS; f++){
			fsm_clear_lights(f);
	}

	switch (current_state){
		case IDLE:
		case MOVING:
		case STOP:
			current_state = EMERGENCY;
			elev_set_stop_lamp(ON);
			break;
		case EMERGENCY:
			while(elev_get_stop_signal()){};
			elev_set_stop_lamp(OFF);
			if(!timer_active()){
				timer_set();
			}

			/*
			 * If timer > WAIT_TIME reset timer, leave emergency
			 */
			if(timer_get() > WAIT_TIME){
				timer_reset();
				current_state = IDLE;
			}
			break;
	}

};

void fsm_ev_button(elev_button_type_t button, int floor){
	order_update(button, floor);
	elev_set_button_lamp(button, floor, ON);
	current_floor = elev_get_floor_sensor_signal();

	switch (current_state){

		case IDLE:
			if(current_floor == -1){
				motor_dir = order_get_dir_d(real_floor);
				elev_set_motor_direction(motor_dir);
				current_state = MOVING;	
				break;
			}

			if(order_get_dir(current_floor) == DIRN_STOP){
				if(orders_none()){
					current_state = IDLE;

				}
				else{
					current_state = STOP;
				}
				break;
			}else{
				//real_floor = elev_get_floor_sensor_signal();
				motor_dir = order_get_dir(current_floor);
				elev_set_motor_direction(motor_dir);
				current_state = MOVING;
				real_floor = real_floor + motor_dir/2.0;
			}
		case MOVING:
			break;
		case STOP:			
			break;
		case EMERGENCY:
			break;
		}

}

state_t fsm_get_state(){
	return current_state;
}

void fsm_clear_lights(int floor){
	for(elev_button_type_t b = BUTTON_CALL_UP; b <= BUTTON_COMMAND; b++){
		/* check that we do not try to acces an element not assosiated with a button */
		if((floor == 0 && b == BUTTON_CALL_DOWN) || (floor == 3 && b == BUTTON_CALL_UP)){
           	continue;
        }
	    else{
			elev_set_button_lamp(b , floor, OFF);
		}
	}
}