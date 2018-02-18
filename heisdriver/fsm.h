#include "elev.h"
//#include "orderSys.h"
#include <stdio.h>
#include <stdbool.h>

#ifndef FSM_H
#define FSM_H



typedef enum state_type {
    IDLE = 0,
    MOVING =1,
    STOP = 3,
    EMERGENCY = 4


} state_t;


static state_t current_state;
static int current_floor;
static int motor_dir;
static int previous_floor;


bool fsm_init();

void fsm_ev_floor_sensor(int floor);

void fsm_ev_button(elev_button_type_t button, int floor);




#endif
