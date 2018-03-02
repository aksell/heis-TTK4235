#include "elev.h"
#include <stdio.h>
#include "fsm.h"

int main() {
    // Initialize hardware
    if (!elev_init()) {
            //initaialiserer heis poisjon
        printf("Unable to initialize elevator hardware!\n");
        return 1;
    }

    if (!fsm_init()){
        printf("Unable to initialize fsm\n");
        return 1;
    }

    //CODE ABOVE: TESTED

    int cycle_num = 0;
    state_t prev_state = IDLE;



    while (1) {
        
        if (elev_get_floor_sensor_signal()!=-1){
            fsm_ev_floor_sensor(elev_get_floor_sensor_signal());
        };
        if (elev_get_stop_signal()){
            fsm_ev_emergency();
        };

        for(int f = 0; f<N_FLOORS; f++){
            for(elev_button_type_t b = BUTTON_CALL_UP; b<=BUTTON_COMMAND; b++){
                if((f==0 && b==BUTTON_CALL_DOWN)||(f==3&&b==BUTTON_CALL_UP)){
                    continue;
                }//to avoid assertion from elev_get_button signal
                else if(elev_get_button_signal(b,f)){
                    fsm_ev_button(b,f);
                }
            }


        }

        //System messages
        cycle_num++;

        if(fsm_get_state() != prev_state){
            printf("Current state: %d, Cycle number: %d",fsm_get_state(),cycle_num);

        }

        prev_state = fsm_get_state();
       
    }

    return 0;
}
