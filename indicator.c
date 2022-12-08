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

int main(void) {

	throttle_toggle_msg_t msg;
	int server_coid, return_status;

	printf("indicator.c now attempting to connect to engine.c\n");

	/* find our server to get a coid*/
	if ((server_coid = name_open(SERVER_NAME, 0)) == -1) {
		return EXIT_FAILURE;
	}
	printf("indicator.c successfully connected to engine.c\n");

	/* send a get message to the server to get a shared memory handle from the server */
	msg.type = INDICATOR_TOGGLE;
	int status = MsgSend(server_coid, &msg, sizeof(msg), return_status, sizeof(return_status));

	printf("indicator.c returned: %d\n", return_status);

     if (status == -1) {
        fprintf(stderr, "Error during MsgSend\n");
        perror(NULL);
        exit(EXIT_FAILURE);
    }

	return EXIT_SUCCESS;
}