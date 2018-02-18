#include "elev.h"
#include <stdio.h>


static int queue[4] = {-1};
static bool active_buttons[N_FLOORS][3] = {{0}};


void order_update((elev_button_type_t button, int floor){
	buttons[f][button] =1;
};

void order_executed(int floor){

	for(int i = 0; i<3;i++){
		active_buttons[f][i] = 0;
	}

	//moves array
	for(int i = 0;i<4;i++){
		if(queue[i]==floor && i!=3){
			for(int j = i, j<3;j++){
				queue[j] = queue[j+1];
			}
			queue[3] = -1;
				
		}
		else if(queue[i]==floor){
			queue[i] = -1;
		}
			}
	}
};


void order_clear(){
	for(int i = 0; i<4; i++){
		queue[i]=-1;
		request_up[i]=0;
		request_down[i]=0;
	}

};


elev_motor_direction_t order_get_dir(int floor){
	if(queue[0]<floor){
		return DIRN_DOWN;
	}
	else if(queue[0]>floor){
		return DIRN_DOWN;
	}
	else if(queue[0]==floor){
		return DIRN_STOP;
	}
	for(int f = 0;f<4;f++){

	}

};

void order_completed(int floor){
	//sett requests + orders at floor to zero, moves queue
}; //de
bool order_should_stop(int floor, elev_motor_direction_t dir){
	for(int i = 0; i<4; i++){
		if(queue[i]==floor){
			
		}
	}
	//check direction of request
	//check if in order list
	return 1;

};
bool orders_none(){
	return 1; //if no orders or requests
};
void order_clear(){	//setter alt til 0

};

