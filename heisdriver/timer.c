#include "timer.h"

void timer_set(){
	timer = time(0);
	active = 1;
};

time_t timer_get(){
	return (time(0)-timer);
};

bool timer_active(){
	return active;
};

void timer_reset(){
	active = 0;
};


/*
void timer_wait(int wait_sec){
	time_t start_time = time(0);

	while(time(0)<(start_time+wait_sec)){
	}

};
*/