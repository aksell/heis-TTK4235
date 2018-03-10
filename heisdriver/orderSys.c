#include "orderSys.h"


void order_update(elev_button_type_t button, int floor) {
	active_buttons[floor][button] = 1;

	/* 
	 * Add new order to queue 
	 */
	if (button == BUTTON_COMMAND) {
		for (int i = 0; i < N_FLOORS; i++) {
			if (queue[i] == floor || queue[i] == -1) {
				queue[i] = floor;
				break;
			}
		}
	}
}


void order_remove(int floor) {
	/*
	 * Delete orders and requests for floor
	 */
	for (int i = 0; i < N_BUTTONS; i++) {
		active_buttons[floor][i] = 0;
	}

	/* 
	 * Move remaining orders forward in queue
	 */
	for (int i = 0; i < N_FLOORS; i++) {
		if (queue[i] == floor) {
			if (i != (N_FLOORS -1)) {
				for (int j = i; j < (N_FLOORS - 1); j++) {
					queue[j] = queue[j + 1];
				}
			};
			queue[N_FLOORS -1] = -1;
		};
	}
}


void order_clear_all() {
	for (int i = 0; i < N_FLOORS; i++) {
		queue[i] = -1;
		for (int j = 0; j < N_BUTTONS; j++) {
			active_buttons[i][j] = 0;
		}
	}

}

bool order_queue_empty(){
	for(int i = 0; i < N_FLOORS; i++){
		if (queue[i] != -1){
			return 0;
		}
	}
	return 1;
}

bool order_finished() {
	for (int i = 0; i < N_FLOORS; i++) {
		if (queue[i] != -1 
			|| active_buttons[i][BUTTON_CALL_UP] != 0 
			|| active_buttons[i][BUTTON_CALL_DOWN] != 0 
			|| active_buttons[i][BUTTON_COMMAND] != 0){
			return 0;
		}
	}
	return 1;
}

bool order_should_stop(int floor, elev_motor_direction_t dir) {
	/* 
	 * Check if the current floor is in queue 
	 */
	for (int i = 0; i < N_FLOORS; i++) {
		if (queue[i] == floor) {
			return 1;
		}
	}
	/* 
	 * Check if the current floor is requested and in same direction
	 */
	if (dir == -1 && active_buttons[floor][BUTTON_CALL_DOWN]) {
		return 1;
	}
	if (dir == 1 && active_buttons[floor][BUTTON_CALL_UP]) {
		return 1;
	}

	if (order_queue_empty() && order_no_request_current_dir(dir) 
		&& (active_buttons[floor][BUTTON_CALL_UP] 
		|| active_buttons[floor][BUTTON_CALL_DOWN])){
		return 1;
	}

	if (((floor==0) 
		&& (active_buttons[0][BUTTON_CALL_UP]||active_buttons[0][BUTTON_CALL_DOWN]))
		||((floor == 3) 
		&& (active_buttons[3][BUTTON_CALL_UP]||active_buttons[3][BUTTON_CALL_DOWN]))){
		return 1;
	}

	return 0;

}

bool order_no_request_current_dir(elev_motor_direction_t dir){
	int button;

	if(dir == -1){
		button = BUTTON_CALL_DOWN;
	}
	if(dir == 1){
		button = BUTTON_CALL_UP;
	}
	for (int i = 0; i < N_FLOORS; i++) {
		if (active_buttons[button][i]) {
			return 0;
		}

	}
	return 1;
}

elev_motor_direction_t order_get_dir(int floor) {

	/* 
	 * Check where first element in queue is 
	 * relative to floor and return direction
	 */
	if (queue[0] < floor && queue[0] != -1) {
		return DIRN_DOWN;
	};
	if (queue[0] > floor && queue[0] != -1) {
		return DIRN_UP;
	};

	if (queue[0] == floor && queue[0] != -1) {
		return DIRN_STOP;
	};

	/*
	 * Return direction relative to current 
	 * floor that has the most requests
	 */
	int requests_up = 0;
	int requests_down = 0;
	for (int f = 0; f < floor; f++) {
		requests_down += active_buttons[f][1];
		requests_down += active_buttons[f][0];
	}
	for (int f = floor + 1; f < N_FLOORS; f++){
		requests_up += active_buttons[f][1];
		requests_up += active_buttons[f][0];
	}
	if (requests_up >= requests_down && requests_up != 0) {
		return DIRN_UP;
	};
	if (requests_down > requests_up) {
		return DIRN_DOWN;
	};
	return DIRN_STOP;

}

elev_motor_direction_t order_get_dir_d(double floor) {

	/* 
	 *Check where first element in queue is 
	 * relative to floor and return direction
	 */
	if (queue[0] < floor && queue[0] != -1) {
		return DIRN_DOWN;
	};
	if (queue[0] > floor && queue[0] != -1) {
		return DIRN_UP;
	};

	if (queue[0] == floor && queue[0] != -1) {
		return DIRN_STOP;
	};

	/*
	 * Return direction relative to current 
	 * floor that has the most requests
	 */
	int requests_up = 0;
	int requests_down = 0;
	for (int f = 0; f < floor; f++) {
		requests_down += active_buttons[f][1];
		requests_down += active_buttons[f][0];
	}
	for (int f = floor + 1; f < N_FLOORS; f++){
		requests_up += active_buttons[f][1];
		requests_up += active_buttons[f][0];
	}
	if (requests_up >= requests_down && requests_up != 0) {
		return DIRN_UP;
	};
	if (requests_down>requests_up) {
		return DIRN_DOWN;
	};
	return DIRN_STOP;

}