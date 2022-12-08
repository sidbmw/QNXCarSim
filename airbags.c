/*
 * airbags.c
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

	airbag_toggle_msg_t msg;
	int server_coid;
	char return_status[256];

	printf("airbags.c now attempting to connect to engine.c\n");

	/* find our server to get a coid*/
	if ((server_coid = name_open(SERVER_NAME, 0)) == -1) {
		return EXIT_FAILURE;
	}
	printf("airbags.c successfully connected to engine.c\n");

	/* send a get message to the server to get a shared memory handle from the server */
	msg.type = AIRBAG_TOGGLE;
	MsgSend(server_coid, &msg, sizeof(msg), return_status, sizeof(return_status));

	printf("airbags.c returned: %s\n", return_status);

	return EXIT_SUCCESS;
}
