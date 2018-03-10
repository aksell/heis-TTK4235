#include "elev.h"
#include "fsm.h"

#include <stdio.h>


int main() {

    /*
     * Initialize elevator hardware
     */
    if (!elev_init()) {
        printf("Unable to initialize elevator hardware!\n");
        return 1;
    }
    if (!fsm_init()){
        printf("Unable to initialize fsm\n");
        return 1;
    }

    /* Number of main loop cycles */
    int cycle_num = 0;

    /* Holds the elevators previous state, used for system messages*/
    state_t prev_state = IDLE;

    int floor;


    while (1) {
        floor = elev_get_floor_sensor_signal();
        if (floor!=-1){
            fsm_ev_floor_sensor(floor);
        };
        if (elev_get_stop_signal() || fsm_get_state()==EMERGENCY){
            fsm_ev_emergency();
        };

        /*
         * Iterate through all buttons, call fsm_ev_button with buttons that are pushed
         */
        for(int f = 0; f<N_FLOORS; f++){
            for(elev_button_type_t b = BUTTON_CALL_UP; b<=BUTTON_COMMAND; b++){
                /*
                 * The first if statement ensures that elements in the
                 * button_channel_matirx not assosciated with a button are not accessed.
                 */
                if(!((f == 0 && b == BUTTON_CALL_DOWN)
                    ||(f == (N_FLOORS -1) && b == BUTTON_CALL_UP))){

                    if(elev_get_button_signal(b,f)){
                        fsm_ev_button(b,f);
                    }
                }
            }
        }

        /*
         * Display system messages to terminal
         */
        cycle_num++;
        if(fsm_get_state() != prev_state){
            printf("Current state: %d, Cycle number: %d \n", fsm_get_state(), cycle_num);
        }
        prev_state = fsm_get_state();
    }
    return 0;
}