
#include <main_view.h>
#include "main.h"

static void
win_delete_request_cb(void *data, Evas_Object *obj, void *event_info)
{
	ui_app_exit();
}

static void
win_back_cb(void *data, Evas_Object *obj, void *event_info)
{
	appdata_s *ad = data;

	/* Let window go to hide state. */
	elm_win_lower(ad->win);
}

static void
create_base_gui(appdata_s *ad)
{
	// Window
	ad->win = elm_win_util_standard_add(PACKAGE, PACKAGE);
	elm_win_autodel_set(ad->win, EINA_TRUE);

	if (elm_win_wm_rotation_supported_get(ad->win)) {
		int rots[4] = { 0, 90, 180, 270 };
		elm_win_wm_rotation_available_rotations_set(ad->win, (const int *)(&rots), 4);
	}

	evas_object_smart_callback_add(ad->win, "delete,request", win_delete_request_cb, NULL);
	eext_object_event_callback_add(ad->win, EEXT_CALLBACK_BACK, win_back_cb, ad);

	// Conformant
	ad->conform = elm_conformant_add(ad->win);
	evas_object_size_hint_weight_set(ad->conform, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	elm_win_resize_object_add(ad->win, ad->conform);
	evas_object_show(ad->conform);

	// Naviframe
	ad->nf = elm_naviframe_add(ad->conform);
	elm_naviframe_prev_btn_auto_pushed_set(ad->nf, EINA_TRUE); /* since Tizen 2.4 */
	elm_object_content_set(ad->conform, ad->nf);
	evas_object_show(ad->nf);

    // Create the first view
	create_main_view(ad);

	evas_object_show(ad->win);
}


static bool
app_create(void *data)
{
	// Выполнение действий до запуска основного цикла
	// Инициализация UI

	appdata_s *ad = data;

	create_base_gui(ad);

	return true;
}

static void
app_control(app_control_h app_control, void *data)
{
	// Выполнение действий при получении запроса на запуск приложения
}

static void
app_pause(void *data)
{
	// Выполнение действий, когда приложение становится невидимым (останавливает работу)
}

static void
app_resume(void *data)
{
	// Выполнение действий, когда приложение становится видимым (возобновляет работу)
}

static void
app_terminate(void *data)
{
	// Выполнение действий, когда приложение завершает работу

}

static void
ui_app_orient_changed(app_event_info_h event_info, void *user_data)
{
	// Выполнение действий при изменении ориентации экрана

	return;
}

int
main(int argc, char *argv[])
{

	// Объявление и инициализация структуры
	appdata_s ad = {0};
	int ret = 0;

	// Объявление и инициализация событий жизненного цикла приложения
	ui_app_lifecycle_callback_s event_callback = {0};

	// Объявление и инициализация обработчиков событий
	//app_event_handler_h handlers[1] = {0};

	// Назначение функций для обработки событий жизненного цикла приложения
	event_callback.create = app_create;
	event_callback.terminate = app_terminate;
	event_callback.pause = app_pause;
	event_callback.resume = app_resume;
	event_callback.app_control = app_control;

	//	Назначение функции для обработки события смены ориентации экрана
	//ui_app_add_event_handler(&handlers[APP_EVENT_DEVICE_ORIENTATION_CHANGED], APP_EVENT_DEVICE_ORIENTATION_CHANGED, ui_app_orient_changed, &ad);

	// Запуск основного цикла (main  loop) программы
	ret = ui_app_main(argc, argv, &event_callback, &ad);
	if (ret != APP_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LOG_TAG, "app_main() is failed. err = %d", ret);
	}

	return ret;
}
