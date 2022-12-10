#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/neutrino.h>
#include <sys/iofunc.h>
#include <sys/dispatch.h>
#include "engine.h"

unsigned short int rpm = 1500;
unsigned char indicator_bit = 0;
int print_details(void);

int main(void) {

    typedef union {
        uint16_t type;
        struct _pulse pulse;
        engine_toggle_msg_t engine_toggle;
        throttle_toggle_msg_t throttle_toggle;
        brakes_toggle_msg_t brakes_toggle;
        indicator_toggle_msg_t indicator_toggle;
        airbag_toggle_msg_t airbag_toggle;
    } recv_buf_t;

    int rcvid;
    name_attach_t *attach;
    recv_buf_t msg;
    char return_msg[256];
    unsigned char airbags_deployed = 0;
    unsigned short int throttle_brake_multiplier = 20;

    //create a channel
    if ((attach = name_attach(NULL, SERVER_NAME, 0)) == NULL) {
        return EXIT_FAILURE;
    }

    printf("Car engine has been turned on and ready...\n");

    //the server should keep receiving, processing and replying to messages
    while (1) {
        //code to receive msg or pulse from client
        rcvid = MsgReceive(attach->chid, &msg, sizeof(msg), NULL);

        if (rcvid == -1) {/* Error condition, exit */
            break;
        }
        //print the returned value of MsgReceive

        //check if it was a pulse or a message
        // if it is a pulse -> check the pulse code to see if the client is gone/disconnected and print (client is gone)  else if the pulse is something else print the code and value of the pulse
        if (rcvid == 0) { /* Pulse received */
            switch (msg.pulse.code) {
            case _PULSE_CODE_DISCONNECT:
                /*
                 * A client disconnected all its connections (called
                 * name_close() for each name_open() of our name) or
                 * terminated
                 */
                printf("Client is gone\n");
                ConnectDetach(msg.pulse.scoid);
                break;

            default:
                /*
                 * A pulse sent by one of your processes or a
                 * _PULSE_CODE_COIDDEATH or _PULSE_CODE_THREADDEATH
                 * from the kernel?
                 */
                printf(
                        "The pulse is something else. Code of the pulse: %d. Value of the pulse: %d.\n",
                        msg.pulse.code, msg.pulse.value.sival_int);
                break;
            }

        } else { // if it was a message
            if(airbags_deployed != 1){ //Do work if
                switch (msg.type) {
                case ENGINE_TOGGLE:
                    printf("In ENGINE_TOGGLE\n");

                    //This will probably be used to turn off the engine
                    //Do work
                    goto exit_loop;
                    break;

                case THROTTLE_TOGGLE:
                    printf("In THROTTLE_TOGGLE\n");

                    //Do some work since throttle toggled
                    //Calculate RPM to be added to current RPM
                    //If we would exceed the redline with rpm + throttle pressure * multiplier then set to 8000 (redline)
                    if(rpm + throttle_brake_multiplier * msg.throttle_toggle.pressure <= 8000){
                        rpm += throttle_brake_multiplier * msg.throttle_toggle.pressure;
                        printf("ACCELERATING!\n\n");
                    } else{
                        rpm = 8000;
                        printf("YOU'RE NOW AT REDLINE!\n\n");
                    }
                    print_details();
                    strcpy(return_msg, "0");
                    MsgReply(rcvid, EOK, &return_msg, sizeof(return_msg));
                    break;

                case BRAKES_TOGGLE:
                    printf("In BRAKES_TOGGLE\n");

                    //Do some work since brakes toggled
                    //If rpm - brake pressure * multiplier less than 1500, just set to 1500 (standstill)
                    if(rpm - throttle_brake_multiplier * msg.brakes_toggle.pressure <= 1500){
                        rpm = 1500;
                        printf("YOU ARE NOW AT A STANDSTILL!\n\n");
                    } else{
                        rpm -= throttle_brake_multiplier * msg.brakes_toggle.pressure;
                        printf("BRAKING!\n\n");
                    }
                    print_details();
                    strcpy(return_msg, "0");
                    MsgReply(rcvid, EOK, &return_msg, sizeof(return_msg));
                    break;

                case INDICATOR_TOGGLE:
                    printf("In INDICATOR_TOGGLE\n");

                    //Do some work since indicators toggled
                    //Manipulate bits for indicators
                    if(indicator_bit == 0){
                        indicator_bit |= msg.indicator_toggle.left_right;
                    } else{
                        if (msg.indicator_toggle.left_right == 0) { //If we want to indicate left..
                            if(indicator_bit == 2){ //..but we already are..
                                indicator_bit ^= 2; //..XOR with 0b10 to turn it off
                            } else{ //..but we are currently indicating right..
                                indicator_bit |= 0; //..OR with 0b00 to flip to indicate left
                            }

                        } else { //If we want to indicate right..
                            if(indicator_bit == 1){ //..but we already are..
                                indicator_bit ^= 1; //..XOR with 0b01 to turn it off
                            } else{ //..but we are currently indicating left..
                                indicator_bit &= 0; //..AND with 0b00 to flip to indicate right
                            }
                        }
                    }

                    print_details();
                    strcpy(return_msg, "0");
                    MsgReply(rcvid, EOK, &return_msg, sizeof(return_msg));
                    break;

                case AIRBAG_TOGGLE:
                    printf("In AIRBAG_TOGGLE\n");

                    //Do some work since airbags deployed
                    //This case and ENGINE_TOGGLE are very similar might remove one of them
                    //If we are here it means airbags were deployed and the car should be shut off
                    //meaning we need to kill and cleanup everything
                    printf("AIRBAGS DEPLOYED! AIRBAGS DEPLOYED! \n\n");
                    rpm = 0;
                    indicator_bit = 3;
                    print_details();
                    goto exit_loop;
                    break;

                default:
                    perror("MsgError\n");
                    break;
                }
            } else { //Airbags were deployed we shouldn't be able to do anything
                strcpy(return_msg, "AIRBAGS ARE DEPLOYED");
                MsgReply(rcvid, EOK, &return_msg, sizeof(return_msg));
            }

        }

    } //Out of while loop

    //remove the name from the namespace and destroy the channel
    exit_loop: name_detach(attach, 0);
    printf("Namespace detached and channel destroyed\n");
    return EXIT_SUCCESS;
}

int print_details(void) {
    printf("\n");

    //Print current RPM
    printf("CURRENT RPM: %d\n", rpm);

    //Print indicator status
    switch (indicator_bit) {
    case 0: //Both indicators off
        printf("BOTH INDICATORS OFF\n");
        break;
    case 1: //Right indicator on
        printf("RIGHT INDICATOR ON\n");
        break;
    case 2: //Left indicator on
        printf("LEFT INDICATOR ON\n");
        break;
    case 3: //Both indicators on
        printf("BOTH INDICATORS ON\n");
        break;
    default:
        printf("INDICATORS DEFAULTED. PLEASE CHECK\n");
        break;
    }

    printf("\n");
    return EXIT_SUCCESS;
}
