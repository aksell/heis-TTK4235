#include "elev.h"
#include "orderSys.h"
#include <stdio.h>

#infdef FSM_H
#define FSM_H



typedef enum state_type {
    IDLE = 0;
    MOVING =1;
    STOP = 2;
    EMERGENCY = 3;


} state_t;


static state_t current_state;
static int current_floor;
static int motor_dir;
static int previous_floor;





int get_current_floor();

int get_motor_dir();



void set_order_lights();

void set_request_lights();

void set_floor_lights();


void open_door();



//events
void fsm_init();

void fsm_ev_floor_sensor(int floor);

void fsm_ev_button();





#endif
