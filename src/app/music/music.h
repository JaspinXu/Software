#pragma once

#include "head.h"

void SendData(uint8_t addr);
void show_number1();
void show_number2();
void show_number3();
lv_obj_t *alarm_load();
void music_alarm_change();
void music_alarm_timer_cb(lv_timer_t *timer);
void alarm_cancel_event(lv_event_t *e);
extern int music_choose_flag;

