/*
 * mport_tizen.c
 *
 *  Created on: Feb 21, 2017
 *      Author: Sergei Papulin
 */

#include <mport_tizen.h>

void message_port_callback(int local_port_id,
		const char *remote_app_id,
		const char *remote_port,
        bool trusted_remote_port,
		bundle *message, void *user_data)
{

	Evas_Object *lbl = user_data;

	char buf[64];

    char *counter = NULL;
    char *status = NULL;

    bundle_get_str(message, "status", &status);
    bundle_get_str(message, "counter", &counter);

    dlog_print(DLOG_INFO, LOG_TAG, "Message from %s, status: %s, counter: %s", remote_app_id, status, counter);

    if (strcmp(status, "starting") == 0) {
    	sprintf(buf, "<font=Sans:style=Regular font_size=50>%s</font>", counter);

    	elm_object_text_set(lbl, buf);

    }
    else if (strcmp(status, "active") == 0) {

    	sprintf(buf, "<font=Sans:style=Regular font_size=50>%s</font>", counter);
    	elm_object_text_set(lbl, buf);
    }
    else if (strcmp(status, "finished") == 0) {

    	sprintf(buf, "<font=Sans:style=Regular font_size=50>%s</font>", "Timer Finished");
    	elm_object_text_set(lbl, buf);
    }


}

void create_message_local_port(messageport_s *mp, Evas_Object *lbl)
{
	char *local_port_name = "AppLocalPort";

	int local_port_id = message_port_register_local_port(local_port_name, message_port_callback, lbl);

	if (local_port_id < 0)
	    dlog_print(DLOG_ERROR, LOG_TAG, "Port register error: %d", local_port_id);
	else
	{
	    dlog_print(DLOG_INFO, LOG_TAG, "local_port_id: %i, local_port_name: %s", local_port_id, local_port_name);

	    mp->local_port_id = local_port_id;
		mp->remote_service = REMOTE_SERVICE_ID;
		mp->local_port_name = local_port_name;
		mp->remote_port_name = "ServiceLocalPort";
	}
}

void send_message_with_local_port(messageport_s *mp, char *maxcounter)
{
    int ret;

    bundle *b = bundle_create();

	bundle_add_str(b, "command", "start");
	bundle_add_str(b, "maxcounter", maxcounter);

    ret = message_port_send_message_with_local_port(mp->remote_service, mp->remote_port_name, b, mp->local_port_id);

    if (ret != MESSAGE_PORT_ERROR_NONE)
        dlog_print(DLOG_ERROR, LOG_TAG, "message_port_send_message_with_local_port error: %d", ret);
    else
        dlog_print(DLOG_INFO, LOG_TAG, "Send message done");

    bundle_free(b);

}

