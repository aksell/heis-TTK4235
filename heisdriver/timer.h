#include <time.h>
#include <stdbool.h>


#ifndef TIMER_H
#define TIMER_H

/* Holds time timer_set was last called*/
static time_t timer;
static bool active;


void timer_set();

time_t timer_get();

void timer_reset();

bool timer_is_active();

#endif