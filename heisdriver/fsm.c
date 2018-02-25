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
	current_floor = elev_get_floor_sensor_signal();

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
			printf("sensor_signal_stop\n");
			motor_dir = DIRN_STOP;
			elev_set_motor_direction(DIRN_STOP);
			elev_set_door_open_lamp(1);
			order_completed(floor);
			timer_wait(3);
			//wait 3 sec check for emergency!!
			//resets all lamps at floor
			for(elev_button_type_t b = BUTTON_CALL_UP; b<=BUTTON_COMMAND; b++){
				if((floor==0 && b==BUTTON_CALL_DOWN)||(floor==3&&b==BUTTON_CALL_UP)){
                    continue;
                }
                else{
					elev_set_button_lamp(b , floor, 0);
				}
			};
			elev_set_door_open_lamp(0);

			if(orders_none()){
				current_state = IDLE;
			}else{
				motor_dir = order_get_dir(floor);
				elev_set_motor_direction(order_get_dir(current_floor));
				current_state=MOVING;
			}
			break;


		case EMERGENCY:
			printf("sensor_signal_emergency\n");
			elev_set_door_open_lamp(1);
			while(elev_get_stop_signal()){};
			elev_set_stop_lamp(0);
			timer_wait(3);
			elev_set_door_open_lamp(0);
			current_state = IDLE;
			break;

		}


}


void fsm_ev_emergency(){
	elev_set_motor_direction(DIRN_STOP);
	motor_dir = DIRN_STOP;
	order_clear();
	elev_set_stop_lamp(1);
	//clear order + request lights
	for(int f=0;f<4;f++){
		for(elev_button_type_t b = BUTTON_CALL_UP; b<=BUTTON_COMMAND; b++){
				if((f==0 && b==BUTTON_CALL_DOWN)||(f==3&&b==BUTTON_CALL_UP)){
                    continue;
                }
                else{
					elev_set_button_lamp(b , f, 0);
				}
			};
	}

	switch (current_state){

		case IDLE:
			printf("em_signal_idle\n");
		case MOVING:
			printf("em_signal_moving\n");
		case STOP:
			printf("em_signal_stop\n");
			current_state = EMERGENCY;
			break;

		case EMERGENCY:
			printf("em_signal_em\n");
			//KAN FLYTTES UDER FSM_EV_EMERGENCY
			while(elev_get_stop_signal()){};
			elev_set_stop_lamp(0);
			timer_wait(3);
			current_state = IDLE;
			break;
	}

};

//because IDLE can either be at floor or no floor


void fsm_ev_button(elev_button_type_t button, int floor){
	order_update(button, floor);
	elev_set_button_lamp(button, floor, 1);

	switch (current_state){

		case IDLE:
			printf("button_signal_idle\n");
			if(order_get_dir(current_floor)==DIRN_STOP){
				printf("hjelp\n");
				current_state = STOP;
				break;
			}else{
				motor_dir = order_get_dir(current_floor);
				elev_set_motor_direction(order_get_dir(current_floor));
				current_state = MOVING;
			}

		case MOVING:
			printf("button_signal_mov\n");
			break;
		case STOP:
			printf("button_signal_stop\n");
			break;
		case EMERGENCY:
			printf("button_signal_em\n");
			break;

		}

}
