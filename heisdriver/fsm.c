#include "fsm.h"

bool fsm_init(){		//Set elev to known current_state//TESTED
	elev_set_motor_direction(DIRN_UP);
    while(elev_get_floor_sensor_signal()==-1){};        //aksel vil gi feilmelding etter timer
    elev_set_motor_direction(DIRN_STOP);
    current_state = IDLE;
    return 1;

}

void fsm_ev_floor_sensor(int floor){		//use current floor, remove floor
	
	elev_set_floor_indicator(floor);
	previous_floor = floor;
	current_floor = floor;

	switch (current_state){

		case IDLE:
			//printf("sensor_signal_idle\n");
			break;

		case MOVING:
			//printf("sensor_signal_moving\n");

			if(order_should_stop(floor, motor_dir)){
				current_state = STOP;
			}
			break;

		case STOP:
			//printf("sensor_signal_stop\n");
			motor_dir = DIRN_STOP;
			elev_set_motor_direction(DIRN_STOP);

			if(!timer_active()){
				timer_set();
			}

			elev_set_door_open_lamp(1);
			order_completed(floor);
			//order_print_queue();
			clear_lights(current_floor);

			if(timer_get()>3){		//poll knapper
				timer_reset();
				elev_set_door_open_lamp(0);

				if(orders_none()){
					current_state = IDLE;
				}else{
					motor_dir = order_get_dir(floor);
					elev_set_motor_direction(order_get_dir(current_floor));
					current_state=MOVING;
				}
			}
			break;


		case EMERGENCY:
			//printf("sensor_signal_emergency\n");
			elev_set_door_open_lamp(1);
			while(elev_get_stop_signal()){};
			elev_set_stop_lamp(0);
			elev_set_door_open_lamp(0);
			current_state = STOP;
			break;

		}


}


void fsm_ev_emergency(){
	elev_set_motor_direction(DIRN_STOP);
	motor_dir = DIRN_STOP;
	order_clear();
	//clear order + request lights
	for(int f = 0;f<4;f++){
			clear_lights(f);
	}
	switch (current_state){

		case IDLE:
			//printf("em_signal_idle\n");
		case MOVING:
			//printf("em_signal_moving\n");
		case STOP:
			//printf("em_signal_stop\n");
			current_state = EMERGENCY;
			elev_set_stop_lamp(1);
			break;

		case EMERGENCY:
			printf("em_signal_stop\n");

			while(elev_get_stop_signal()){};
			elev_set_stop_lamp(0);
			if(!timer_active()){
				printf("timer reset\n");

				timer_set();
			}

			if(timer_get()>3){		//poll knapper
				timer_reset();
				printf("freeeeeeee\n");

				current_state = IDLE;
			}
			break;
	}

};

//because IDLE can either be at floor or no floor


void fsm_ev_button(elev_button_type_t button, int floor){
	order_update(button, floor);
	//order_print_queue();
	elev_set_button_lamp(button, floor, 1);
	current_floor = elev_get_floor_sensor_signal();


	switch (current_state){

		case IDLE:
		printf("%i ey aiyhaaaaaaa\n", elev_get_floor_sensor_signal());
			if(current_floor==-1){
				motor_dir = order_get_dir_d((current_floor+previous_floor)/2.0);
				elev_set_motor_direction(motor_dir);
				current_state = MOVING;	
			}
			//printf("button_signal_idle\n");
			if(order_get_dir(current_floor)==DIRN_STOP){
				if(orders_none()){
					current_state = IDLE;

				}
				else{current_state = STOP;}
				break;
			}else{
				printf("-1\n");
				motor_dir = order_get_dir(current_floor);
				elev_set_motor_direction(motor_dir);
				current_state = MOVING;
			}

		case MOVING:
			//printf("button_signal_mov\n");
			break;
		case STOP:			
			break;
		case EMERGENCY:
			//printf("button_signal_em\n");
			break;

		}

}

state_t fsm_get_state(){
	return current_state;
}

void clear_lights(int floor){
	for(elev_button_type_t b = BUTTON_CALL_UP; b<=BUTTON_COMMAND; b++){
		if((floor==0 && b==BUTTON_CALL_DOWN)||(floor==3&&b==BUTTON_CALL_UP)){
           	continue;
        }
	    else{
			elev_set_button_lamp(b , floor, 0);
		}
	}
}