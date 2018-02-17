#include "fsm.h"

bool fsm_init(){		//Set elev to known current_state//TESTED
	elev_set_motor_direction(DIRN_UP);
    while(elev_get_floor_sensor_signal()==-1){};        //aksel vil gi feilmelding etter timer
    elev_set_motor_direction(DIRN_STOP);
    current_state = EMERGENCY;
    return 1;
	
}


void fsm_ev_floor_sensor(int floor){
	
	if(floor != -1 && previous_floor != floor){		//updates floor
		previous_floor = floor;
		elev_set_floor_indicator(previous_floor);
 	};
 	current_floor = floor;

	switch (current_state){

		case IDLE:
			break;

		case MOVING:
		
			motor_dir = order_get_dir();
			elev_set_motor_direction(order_get_dir());

			if(order_should_stop(previous_floor, motor_dir)){
				current_state = STOP;
			}
			break;

		case STOP:
		
			elev_set_motor_direction(DIRN_STOP);
			elev_set_door_open_lamp(1);
			order_executed(previous_floor); 			//Delete order and update orders
			//wait 3 sec check for emergency
			for(elev_button_type_t b = BUTTON_CALL_UP; b<=BUTTON_COMMAND; b++){
				elev_set_button_lamp(b , previous_floor, 0);
			};
			elev_set_door_open_lamp(0);

			if(no orders){
				current_state = IDLE;
			}else{
				current_state=MOVING;
			}
			break;
			

		case EMERGENCY:
			elev_set_door_open_lamp(1);
			while(elev_get_stop_signal()){};
			elev_set_stop_lamp(0);
			//timer 3 sec
			elev_set_door_open_lamp(0);
			current_state = IDLE;
			break;

		}


}


void fsm_ev_emergency(){
	elev_set_motor_direction(DIRN_STOP);
	order_clear();
	elev_set_stop_lamp(1);
	//clear order + request lights

	switch (current_state){

		case IDLE:
		case MOVING:
		case STOP:
			current_state = EMERGENCY;
			break;

		case EMERGENCY:
			//KAN FLYTTES UDER FSM_EV_EMERGENCY
			while(elev_get_stop_signal()){};
			elev_set_stop_lamp(0);
			current_state = IDLE;
			break;
	}

};

//because IDLE can either be at floor or no floor


void fsm_ev_button(elev_button_type_t button, int floor){
	update_orders(button, floor);
	elev_set_button_lamp(button, floor, 1);

	switch (current_state){

		case IDLE:
			current_state = MOVING;

		case MOVING:
			motor_dir = order_get_dir();
			elev_set_motor_direction(order_get_dir());
			break;

		case STOP:
			current_state = STOP;
			break;

		case EMERGENCY:
			current_state = EMERGENCY;
			break;

		}

}







