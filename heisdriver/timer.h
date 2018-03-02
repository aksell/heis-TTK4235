#include <time.h>
#include <stdbool.h>

#ifndef TIMER_H
#define TIMER_H

static time_t timer;
static bool active;


void timer_set();
time_t timer_get();
void timer_reset();
bool timer_active();

#endif