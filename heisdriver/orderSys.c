#include "orderSys.h"

void print_queue(){
	for(int f = 0; f<4;f++){
			printf(queue[i] + "\t" );
	}
}

void print_buttons(){
	for(int f = 0; f<4;f++){
		for(int b = 0; b<3;b++){
			printf(active_buttons[f][i] + "\t" );
		}
		printf("\n", );
	}
}

void order_update(elev_button_type_t button, int floor){
	buttons[f][button] =1;
	//adds to queue
	if(button == BUTTON_COMMAND){
		for(int i = 0; i<4; i++){
			if(queue[i]==floor||queue[i]==-1){
				queue[i]=floor;
				break;
			}
		}
	}
}

void order_completed(int floor){

	for(int i = 0; i<3;i++){
		active_buttons[f][i] = 0;
	}

	//moves array
	for(int i = 0;i<4;i++){
		if(queue[i]==floor){
			if(i!=3){
				for(int j = i, j<3;j++){
					queue[j] = queue[j+1];
				}
			};
			queue[3] = -1;
		};
	}
}

void order_clear(){
	for(int i = 0; i<4; i++){
		queue[i]=-1;
		for(int j = 0;j<3;i++){
			buttons[i][j]=0;
		}
	}

}

elev_motor_direction_t order_get_dir(int floor){
	if(queue[0]<floor){
		return DIRN_DOWN;
	};
	if(queue[0]>floor){
		return DIRN_DOWN;
	};
	if(queue[0]==floor){
		return DIRN_STOP;
	};

	int reqests_up=0;
	int requests_down =0;
	for(int f = 0;f<4;f++){
		requests_up+=active_buttons[i][0];
		requests_down+=active_buttons[i][1];
	}

	if(requests_up >=requests_down && requests_up!=0){
		return DIRN_UP;
	};
	if(requests_down>requests_up){
		return DIRN_DOWN;
	};
	return DIRN_STOP;

}

bool order_should_stop(int floor, elev_motor_direction_t dir){
	//Check if in queue
	for(int i = 0; i<4; i++){
		if(queue[i]==floor){
				return 1;
		}
	}
	//check if requested
	if (dir == -1 && active_buttons[floor][1]==1) {
		return 1;
	}
	if (dir == 1 && active_buttons[floor][0]) {
		return 1;
	}

	return 0;

};

bool orders_none(){
	for (int i = 0; i < 4; i++) {
		if (queue[i]!=-1 || active_buttons[i]!={0,0,0}) {
			return 0;
		}
	}
	return 1;
};
