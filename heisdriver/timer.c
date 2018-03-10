#include "timer.h"


void timer_set(){
	timer = time(0);
	active = 1;
};

time_t timer_get(){
	return (time(0)-timer);
};

bool timer_is_active(){
	return active;
};

void timer_reset(){
	active = 0;
};