#include "elev.h"
#include <stdio.h>
#include <stdbool.h>

#ifndef ORDERSYS_H
#define ORDERSYS_H

static int queue[4] = {-1,-1,-1,-1};
static bool active_buttons[N_FLOORS][3] = {{0}};


void order_update(elev_button_type_t button, int floor);

void order_completed(int floor);

bool order_should_stop(int floor, elev_motor_direction_t dir);

bool orders_finished();

void order_clear();

void order_print_queue();

bool order_no_request_current_dir(elev_motor_direction_t dir);

bool queue_empty();


elev_motor_direction_t order_get_dir(int floor);

elev_motor_direction_t order_get_dir_d(double floor);

#endif