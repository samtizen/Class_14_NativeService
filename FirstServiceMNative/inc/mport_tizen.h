/*
 * mport_tizen.h
 *
 *  Created on: Feb 21, 2017
 *      Author: Sergei Papulin
 */

#ifndef MPORT_TIZEN_H_
#define MPORT_TIZEN_H_

#include <message_port.h>

void create_message_local_port();
void message_port_callback(int local_port_id, const char *remote_app_id, const char *remote_port, bool trusted_remote_port, bundle *message, void *user_data);
void send_message_with_local_port(int local_port_id, char *remote_app_id, char *remote_port_name, int counter, int isFinished);

void start_timer(int counter, int local_port_id, char *remote_app_id, char *remote_port_name);

#endif /* MPORT_TIZEN_H_ */
