/*
 * brakes.c
 */

#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/neutrino.h>
#include <sys/iofunc.h>
#include <sys/dispatch.h>

#include "engine.h" // defines messages between client and server

int main(int argc, char **argv) {

    throttle_toggle_msg_t msg;
    int server_coid, status;
    char return_status[256];
    int pressure;

    if (argc != 2){
        printf("Error: Must have two arguments\n");
        exit(EXIT_FAILURE);
    }
    pressure = atoi(argv[1]);
    printf("brakes.c now attempting to connect to engine.c\n");

    /* find our server to get a coid*/
    if ((server_coid = name_open(SERVER_NAME, 0)) == -1) {
        return EXIT_FAILURE;
    }
    printf("brakes.c successfully connected to engine.c\n");

    /* send a get message to the server to get a shared memory handle from the server */
    msg.type = BRAKES_TOGGLE;
    msg.pressure = pressure;
    status = MsgSend(server_coid, &msg, sizeof(msg), return_status, sizeof(return_status));

    printf("brakes.c returned: %s\n", return_status);

    if (status == -1) {
        fprintf(stderr, "Error during MsgSend\n");
        perror(NULL);
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}
