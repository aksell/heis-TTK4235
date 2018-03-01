#include "orderSys.h"

/*
void print_queue(){
	for(int f = 0; f<4;f++){
			printf(queue[f] + "\t" );
	}
}

void print_buttons(){
	for(int f = 0; f<4;f++){
		for(int b = 0; b<3;b++){
			printf(active_buttons[f][b] + "\t" );
		}
		printf("\n");
	}
}

*/

void order_update(elev_button_type_t button, int floor) {
	active_buttons[floor][button] = 1;
	//adds to queue
	if (button == BUTTON_COMMAND) {
		for (int i = 0; i<4; i++) {
			if (queue[i] == floor || queue[i] == -1) {
				queue[i] = floor;
				printf("queue: %i\n", floor);
				break;
			}
		}
	}
}

void order_completed(int floor) {

	for (int i = 0; i<3; i++) {
		active_buttons[floor][i] = 0;
	}

	//moves array
	for (int i = 0; i<4; i++) {
		if (queue[i] == floor) {
			if (i != 3) {
				for (int j = i; j < 3; j++) {
					queue[j] = queue[j + 1];
				}
			};
			queue[3] = -1;
		};
	}
}

void order_clear() {
	for (int i = 0; i<4; i++) {
		queue[i] = -1;
		for (int j = 0; j<3; j++) {
			active_buttons[i][j] = 0;
		}
	}

}

elev_motor_direction_t order_get_dir(int floor) {
	printf("%i floor\n",floor);

	if (queue[0]<floor && queue[0]!=-1) {
		return DIRN_DOWN;
	};
	if (queue[0]>floor && queue[0]!=-1) {
		return DIRN_UP;
	};
	if (queue[0] == floor && queue[0]!=-1) {
		return DIRN_STOP;
	};


	if (active_buttons[floor][1] || active_buttons[floor][0]) {
		printf("2\n");

		return DIRN_STOP;

	}
	int requests_up = 0;		//above
	int requests_down = 0;
	for (int f = 0; f<floor; f++) {
		requests_down += active_buttons[f][1];
		requests_down += active_buttons[f][0];
	}
	for (int f = floor+1; f < 4; f++){
		requests_up += active_buttons[f][1];
		requests_up += active_buttons[f][0];
	}

	if (requests_up >= requests_down && requests_up != 0) {
		return DIRN_UP;
	};
	if (requests_down>requests_up) {
		return DIRN_DOWN;
	};
	
	printf("end\n");

	return DIRN_STOP;



}


//returns 1 if no request in current direction
bool order_no_request_current_dir(elev_motor_direction_t dir){
	int button;

	if(dir == -1){
		button = 1; //BUTTON_CALL_DOWN
	}
	if(dir == 1){
		button = 0; //BUTTON_CALL_UP
	}
	for (int i = 0; i < 4; i++) {
		if (active_buttons[button][i]) {
			return 0;
		}

	}
	return 1;
};



bool order_should_stop(int floor, elev_motor_direction_t dir) {
	//Check if in queue
	for (int i = 0; i<4; i++) {
		if (queue[i] == floor) {
			return 1;
		}
	}
	//check if requested
	if (dir == -1 && active_buttons[floor][1]) {
		return 1;
	}
	if (dir == 1 && active_buttons[floor][0]) {
		return 1;
	}

	if (order_no_request_current_dir(dir) && (active_buttons[floor][0] || active_buttons[floor][1])){
		return 1;
	}

	return 0;

};


bool orders_none() {
	for (int i = 0; i < 4; i++) {
		if (queue[i] != -1 || active_buttons[i][0] != 0 || active_buttons[i][1] != 0 ||  active_buttons[i][2] != 0) {
			return 0;
		}

	}
	return 1;
};

