#include "fsm.h"



int get_current_floor(){
	return current_floor;
}

int get_motor_dir(){
	return motor_dir;
}



void set_order_lights(){
    for(int i = 0; i < 4; i++){
    	elev_set_button_lamp(BUTTON_COMMAND , i, get_order_list[i]);
    }
}


void set_request_lights(){
    for(int i = 0; i < N_BUTTONS; i++){
    	for(int j = 0; j < 2; j++)
    		elev_set_button_lamp(i, j, get_request_list(i,j));
    }
}

void set_floor_lights(){
		elev_set_button_lamp(current_floor);
}

void open_door(){

}





void fsm_init(){
	
}


void fsm_ev_floor_sensor(int floor){
	
	if(floor != -1 && previous_floor != floor){
	previous_floor = floor;
	set_floor_lights(floor);
 	}
 	current_floor = floor;

	switch (current_state):

		case IDLE:

			break;

		case MOVING:
			if(get_should_stop(current_floor, motor_dir)){
				current_state = STOP;
			}
			
		}
		break;

		case STOP:
			open_door();
			order_executed(current_floor);

			set_door_lights();
			close_door();
			reset_door_lighs();

			break;

		case EMERGENCY:

}


void fsm_ev_button(){


}

	







}