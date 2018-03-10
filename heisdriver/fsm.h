#include "elev.h"
#include "orderSys.h"
#include "timer.h"

#include <stdio.h>
#include <stdbool.h>


#ifndef FSM_H
#define FSM_H

/* Time to wait when door is open */
#define WAIT_TIME 3

#define ON 1
#define OFF 0

typedef enum state_type {
    IDLE = 0,
    MOVING =1,
    STOP = 2,
    EMERGENCY = 3


} state_t;

static state_t current_state;
static int current_floor;
static int motor_dir;
static double real_floor;

/* 
 * Moves elevator to a known states
 */
bool fsm_init();

/*
 * Elevator events are handled by their respective fsm_event function 
 */
void fsm_ev_floor_sensor(int floor);

void fsm_ev_emergency();

void fsm_ev_button(elev_button_type_t button, int floor);

/*
 * Returns the current state
 */
state_t fsm_get_state();

/*
 * Clear order lights and request lights
 */
void fsm_clear_lights();

#endif
