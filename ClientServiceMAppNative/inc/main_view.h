/*
 * mainiview.h
 *
 *  Created on: Feb 20, 2017
 *      Author: Sergei Papulin
 */

#ifndef MAIN_VIEW_H_
#define MAIN_VIEW_H_

#include "main.h"

void create_main_view(appdata_s *ad);

void start_timer_btn_clicked_cb(void *data, Evas_Object *obj, void *event_info);
void create_port_btn_clicked_cb(void *data, Evas_Object *obj, void *event_info);

#endif /* MAIN_VIEW_H_ */
