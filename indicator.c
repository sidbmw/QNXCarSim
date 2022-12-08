/*
 * indicator.c
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

    indicator_toggle_msg_t msg;
    int server_coid, status;
    char return_status[256];
    char *left_right;

	if (argc != 1){
        printf("Error: not enough arguments\n");
        exit(EXIT_FAILURE);
    }

	left_right = argv[1];

    if (argc != 2){
        printf("Error: Must have two arguments\n");
        exit(EXIT_FAILURE);
    }

    left_right = argv[1];

    printf("indicator.c now attempting to connect to engine.c\n");
	/* send a get message to the server to get a shared memory handle from the server */
	msg.type = INDICATOR_TOGGLE;

	if (left_right == "l") {
		msg.left_right = 0;
	}
	else if (left_right == "r") {
		msg.left_right = 1;
	}
	else {
		printf("Error: not a valid argument\n");
        exit(EXIT_FAILURE);
	}
	int status = MsgSend(server_coid, &msg, sizeof(msg), return_status, sizeof(return_status));

    /* find our server to get a coid*/
    if ((server_coid = name_open(SERVER_NAME, 0)) == -1) {
        return EXIT_FAILURE;
    }
    printf("indicator.c successfully connected to engine.c\n");

    /* send a get message to the server to get a shared memory handle from the server */
    msg.type = INDICATOR_TOGGLE;

    if (strcmp(left_right, "l" ) == 0) {
        msg.left_right = 0;
    }
    else if (strcmp(left_right, "r") == 0) {
        msg.left_right = 1;
    }
    else {
        printf("Error: not a valid argument\n");
        exit(EXIT_FAILURE);
    }
    status = MsgSend(server_coid, &msg, sizeof(msg), return_status, sizeof(return_status));

    printf("indicator.c returned: %s\n", return_status);

    if (status == -1) {
        fprintf(stderr, "Error during MsgSend\n");
        perror(NULL);
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}
