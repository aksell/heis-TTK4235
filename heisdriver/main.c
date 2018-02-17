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





    while (1) {

        fsm_ev_floor_sensor(elev_get_floor_sensor_signal());
        /*
        if (elev_get_stop_signal()){
                   fsm_ev_emergency(); 
        }


        for(int f = 0; f<N_FLOORS; b++){
            for(elev_button_type_t b = BUTTON_CALL_UP; b<=BUTTON_COMMAND; b++){
                if(elev_get_button_signal(b,f)){
                    fsm_ev_button(b,f);
                }
            }
            
            */
        }
    


    return 0;
}
