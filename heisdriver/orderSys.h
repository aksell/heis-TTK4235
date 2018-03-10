#include "elev.h"
#include <stdio.h>
#include <stdbool.h>

#ifndef ORDERSYS_H
#define ORDERSYS_H

/* orders are stored chronologically in the queue */
static int queue[4] = {-1,-1,-1,-1};
static bool active_buttons[N_FLOORS][3] = {{0}};


void order_update(elev_button_type_t button, int floor);

void order_remove(int floor);

bool order_should_stop(int floor, elev_motor_direction_t dir);

bool orders_finished();

void order_clear_all();


/*
 * Returns true if there are no requests in the current direction
 */
bool order_no_request_current_dir(elev_motor_direction_t dir);


/*
 * order_get_dir returns the direction the elevator should travel
 * to complete orders or requests. Orders are completed in order.
 * Orders have priority over requests, and wil be serviced first. 
 */
elev_motor_direction_t order_get_dir(int floor);

/*
 * order_get_dir_d returns the direction when the elevator is stopped
 * between floors e.g floor 1.5 when elevator is between first and second
 */
elev_motor_direction_t order_get_dir_d(double floor);

#endif