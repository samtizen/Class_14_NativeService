/*
 * mport_tizen.h
 *
 *  Created on: Feb 21, 2017
 *      Author: Sergei Papulin
 */

#ifndef MPORT_TIZEN_H_
#define MPORT_TIZEN_H_

#include "main.h"

void send_message_with_local_port(messageport_s *mp, char *maxcounter);
void create_message_local_port(messageport_s *mp, Evas_Object *lbl);
void message_port_callback(int local_port_id, const char *remote_app_id, const char *remote_port, bool trusted_remote_port, bundle *message, void *user_data);

#endif /* MPORT_TIZEN_H_ */
