/*
 * mport_tizen.c
 *
 *  Created on: Feb 21, 2017
 *      Author: Sergei Papulin
 */
#include "main_service.h"
#include "mport_tizen.h"
#include "timer.h"

void create_message_local_port()
{
	char *local_port_name = "ServiceLocalPort";

	int local_port_id = message_port_register_local_port(local_port_name, message_port_callback, NULL);

	if (local_port_id < 0)
	    dlog_print(DLOG_ERROR, LOG_TAG, "Port register error: %d", local_port_id);
	else
	    dlog_print(DLOG_INFO, LOG_TAG, "local_port_id: %i, local_port_name: %s", local_port_id, local_port_name);
}

void message_port_callback(int local_port_id,
		const char *remote_app_id,
		const char *remote_port,
        bool trusted_remote_port,
		bundle *message, void *user_data)
{
    int ret;

    char *command = NULL;
    char *str_counter = NULL;

    bundle_get_str(message, "command", &command);
    bundle_get_str(message, "maxcounter", &str_counter);

    dlog_print(DLOG_INFO, LOG_TAG, "Message from %s, command: %s data: %s", remote_app_id, command, str_counter);

    if (strcmp(command, "start") == 0) {

		bundle *reply = bundle_create();

		bundle_add_str(reply, "status", "starting");
		bundle_add_str(reply, "counter", "0");

		ret = message_port_send_message(remote_app_id, remote_port, reply);

		bundle_free(reply);

	    if (ret != MESSAGE_PORT_ERROR_NONE)
	        dlog_print(DLOG_ERROR, LOG_TAG, "Port send message error: %d", ret);

		//int counter = atoi(str_counter);
	    //int counter = strtol(str_counter, NULL, 10);

	    int counter;

	    sscanf(str_counter, "%i", &counter);

		start_timer(counter, local_port_id, remote_app_id, remote_port);
    }

}

void send_message_with_local_port(int local_port_id, char *remote_app_id, char *remote_port_name, int counter, int isFinished)
{
    int ret;

    bundle *b = bundle_create();

    if (isFinished == 1) {

		bundle_add_str(b, "status", "finished");
		bundle_add_str(b, "counter", "-1");
    }
    else
    {
		char str_counter[64];

		sprintf(str_counter, "%d", counter);

		bundle_add_str(b, "status", "active");
		bundle_add_str(b, "counter", str_counter);
    }

    ret = message_port_send_message_with_local_port(remote_app_id, remote_port_name, b, local_port_id);

    if (ret != MESSAGE_PORT_ERROR_NONE)
        dlog_print(DLOG_ERROR, LOG_TAG, "message_port_send_message_with_local_port error: %d", ret);
    else
        dlog_print(DLOG_INFO, LOG_TAG, "Send message done");

    bundle_free(b);

}

void start_timer(int counter, int local_port_id, char *remote_app_id, char *remote_port_name)
{
	int i = 0;

	for(i; i < counter; i++)
	{
		one_second_timer();
		send_message_with_local_port(local_port_id, remote_app_id, remote_port_name, i+1, 0);
	}

	send_message_with_local_port(local_port_id, remote_app_id, remote_port_name, i+1, 1);
}
