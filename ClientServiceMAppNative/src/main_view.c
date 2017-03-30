/*
 * main_view.c
 *
 *  Created on: Feb 20, 2017
 *      Author: Sergei Papulin
 *
 *
 *
 */

#include <main_view.h>
#include <mport_tizen.h>

// Создание формы first view
void create_main_view(appdata_s *ad)
{
	Evas_Object *content, *btn_nav, *btn_cont, *entry, *lbl;
	Elm_Object_Item *nf_it;

	// Box
	content = elm_box_add(ad->nf); // создаем контейнер типа box
	elm_box_align_set(content, 0, 0); // устанавливает его положение (верхний левый угол)
	evas_object_show(content);	// устанавливаем свойство visible в true

	// Label для отображения текущего значения счетчика
	lbl = elm_label_add(content);
	elm_object_text_set(lbl, "Enter Number");
	evas_object_size_hint_weight_set(lbl, EVAS_HINT_EXPAND, 0.1);
	evas_object_size_hint_align_set(lbl, 0, 0);
	evas_object_show(lbl);
	elm_box_pack_start(content, lbl);

	// Текстовое поле
	entry = elm_entry_add(content); // создаем текстовое поле ввода
	elm_entry_single_line_set(entry, EINA_TRUE);
	elm_entry_entry_set(entry, "0"); // устанавливаем исходный текст поля
	evas_object_size_hint_align_set(entry, EVAS_HINT_FILL, EVAS_HINT_FILL); // текстовое поле будет заполнять родительский элемент
	evas_object_size_hint_weight_set(entry, 0, 0); // размещение элемента в пространстве с максимальной величиной по горизонтали  и на 0.5 по вертикали
	evas_object_show(entry); // устанавливаем свойство текстового поля visible=true
	elm_box_pack_end(content, entry); // добавляем поле в начало контейнера box
	ad->txt = entry;

	// Кнопка в box'е для создания порта
	btn_cont = elm_button_add(content); // создаем кнопку в content для перехода на следующую страницу
	elm_object_text_set(btn_cont, "Create Port"); // уcтанавливаем текст
	evas_object_size_hint_min_set(btn_cont, 400, 128); // уcтанавливаем размер
	evas_object_size_hint_align_set(btn_cont, 0.5, 1); // определяем положение кнопки (внизу в центре)
	evas_object_size_hint_weight_set(btn_cont, EVAS_HINT_EXPAND, 0.3); // размещение элемента в пространстве с максимальной величиной по горизонтали  и на 0.5 по вертикали
	evas_object_smart_callback_add(btn_cont, "clicked",create_port_btn_clicked_cb, ad); // устанавливаем обработчик события clicked
	evas_object_show(btn_cont); // устанавливаем свойство кнопки visible=true
	elm_box_pack_end(content, btn_cont); // добавляем кнопку в конец контейнера box

	// Кнопка в box'е для отправки сообщения
	btn_nav = elm_button_add(content); // создаем кнопку в content для перехода на следующую страницу
	elm_object_text_set(btn_nav, "Start Timer"); // уcтанавливаем текст
	evas_object_size_hint_min_set(btn_nav, 400, 128); // уcтанавливаем размер
	evas_object_size_hint_align_set(btn_nav, 0.5, 0); // определяем положение кнопки (внизу в центре)
	evas_object_size_hint_weight_set(btn_nav, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND); // размещение элемента в пространстве с максимальной величиной по горизонтали  и на 0.5 по вертикали
	evas_object_smart_callback_add(btn_nav, "clicked", start_timer_btn_clicked_cb, ad); // устанавливаем обработчик события clicked
	evas_object_show(btn_nav); // устанавливаем свойство кнопки visible=true
	elm_box_pack_end(content, btn_nav); // добавляем кнопку в конец контейнера box

	// Label для наименования
	lbl = elm_label_add(content);
	elm_object_text_set(lbl, "Counter State");
	evas_object_size_hint_weight_set(lbl, EVAS_HINT_EXPAND, 0.1);
	evas_object_size_hint_align_set(lbl, 0, 0.5);
	evas_object_show(lbl);
	elm_box_pack_end(content, lbl);

	// Label для отображения текущего значения счетчика
	lbl = elm_label_add(content);
	elm_object_text_set(lbl, "None");
	evas_object_size_hint_weight_set(lbl, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(lbl, 0.5, 0.5);
	evas_object_show(lbl);
	elm_box_pack_end(content, lbl);
	ad->lbl = lbl;

	// Добавляем naviframe в массив naviframe (верхний view отображается на экране)
	nf_it = elm_naviframe_item_push(ad->nf, "Main View", NULL, NULL, content, NULL); // добавляем nf в массив элементов naviframe

}

void create_port_btn_clicked_cb(void *data, Evas_Object *obj, void *event_info)
{
	appdata_s *ad = data;

	ad->mp = calloc(1 , sizeof(messageport_s));

	create_message_local_port(ad->mp, ad->lbl);

	dlog_print(DLOG_INFO, LOG_TAG, "Port Created");
}

void start_timer_btn_clicked_cb(void *data, Evas_Object *obj, void *event_info)
{
	appdata_s *ad = data;

	//int maxcounter = atoi(elm_object_text_get(ad->txt));
	send_message_with_local_port(ad->mp, elm_object_text_get(ad->txt));
}

