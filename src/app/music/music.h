/*
 * @Author: JaspinXu sea.xuo@gmail.com
 * @Date: 2024-05-04 10:32:54
 * @LastEditors: JaspinXu sea.xuo@gmail.com
 * @LastEditTime: 2024-07-01 00:54:06
 * @FilePath: \Software\src\app\music\music.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#ifndef __MUSIC_H_
#define __MUSIC_H_

#include "head.h"

#ifndef music_pin 12
#endif

#ifdef __cplusplus
extern "C" {
#endif
void SendData(char addr);
void show_number1();
void show_number2();
void show_number3();
lv_obj_t *alarm_load();
void music_alarm_change();
void music_alarm_timer_cb(lv_timer_t *timer);
void alarm_cancel_event(lv_event_t *e);
LV_IMG_DECLARE(_1_alpha_155x160);
extern int music_choose_flag;
#ifdef __cplusplus
} /* extern "C" */
#endif


#endif

