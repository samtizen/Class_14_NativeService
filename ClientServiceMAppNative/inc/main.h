#ifndef __main_H__
#define __main_H__

#include <app.h>
#include <Elementary.h>
#include <system_settings.h>
#include <efl_extension.h>
#include <dlog.h>
#include <time.h>
#include <message_port.h>

typedef struct MessagePort
{
	int local_port_id;
	char *local_port_name;
	char *remote_port_name;
	char *remote_service;

} messageport_s;

typedef struct appdata {

	Evas_Object *win;
	Evas_Object *conform;
	Evas_Object *nf;
	Evas_Object *txt;
	Evas_Object *lbl;
	messageport_s *mp;

} appdata_s;


#ifdef  LOG_TAG
#undef  LOG_TAG
#endif
#define LOG_TAG "clientservicemappnative"

#define REMOTE_SERVICE_ID "org.example.firstservicemnative"

#if !defined(PACKAGE)
#define PACKAGE "org.example.clientservicemappnative"
#endif

#endif /* __clientservicemappnative_H__ */
