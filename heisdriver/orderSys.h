#include "elev.h"
#include <stdio.h>
#include <stdbool.h>

#ifndef ORDERSYS_H
#define ORDERSYS_H

/* Orders are stored chronologically in the queue */
static int queue[4] = {-1,-1,-1,-1};
/* Requests are stored in activ_buttons */
static bool active_buttons[N_FLOORS][3] = {{0}};

/*
 * Add new orders to queue and new requestes to actice_buttons.
 */
void order_update(elev_button_type_t button, int floor);

/*
 * Remove orders and requests for the floor given.
 */
void order_remove(int floor);

/*
 * Clear all orders and requests.
 */
void order_clear_all();

/*
 * Returns true if the queue is empty.
 */
bool order_queue_empty();

/*
 * Returns true when all orders and requests are completed.
 */
bool order_finished();

/*
 * Determines if the elevator should stop when it reaches a floor.
 */
bool order_should_stop(int floor, elev_motor_direction_t dir);

/*
 * Returns true if there are no requests in the current direction.
 */
bool order_no_request_current_dir(elev_motor_direction_t dir);


/*
 * Order_get_dir returns the direction the elevator should travel
 * to complete orders or requests. Orders are completed in chronologically.
 * Orders have priority over requests, and wil be serviced first. 
 */
elev_motor_direction_t order_get_dir(int floor);

/*
 * Order_get_dir_d returns the direction when the elevator is stopped
 * between floors, e.g floor 1.5 when elevator is between first and second.
 */
elev_motor_direction_t order_get_dir_d(double floor);

#endif