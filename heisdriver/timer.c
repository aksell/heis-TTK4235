#include "timer.h"


void timer_wait(int wait_sec){
	time_t start_time = time(0);

	while(time(0)<(start_time+wait_sec)){
	}

};
