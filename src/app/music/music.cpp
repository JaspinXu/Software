#include "music.h"
double music_alarmFlag = 0;
lv_timer_t *music_alarm_timer;

void SendData(uint8_t addr) 
{
    digitalWrite(music_pin, HIGH); 
    delayMicroseconds(1000);
    digitalWrite(music_pin, LOW); 
    delayMicroseconds(3200);   
    for (uint8_t i = 0; i < 8; i++)  
    {
        digitalWrite(music_pin, HIGH);
        if (addr & 0x01) 
        {
            delayMicroseconds(600);
            digitalWrite(music_pin, LOW);
            delayMicroseconds(200);
        }
        else 
        {
            delayMicroseconds(200);
            digitalWrite(music_pin, LOW);
            delayMicroseconds(600);
        }
        addr >>= 1;
    }
    digitalWrite(music_pin, HIGH);
}

void show_number1()
{
    SendData(0x0a); 
    SendData(0x09); 
    SendData(0x00);
    SendData(0x0c); 
    delay(2000);   

    SendData(0x0a); 
    SendData(0x01); 
    SendData(0x0b); 
}

void show_number2()
{
    SendData(0x0a); 
    SendData(0x09); 
    SendData(0x00);
    SendData(0x0c); 
    delay(2000);     


    SendData(0x0a); 
    SendData(0x02); 
    SendData(0x0b); 
}

void show_number3()
{
    SendData(0x0a); 
    SendData(0x09); 
    SendData(0x00);
    SendData(0x0c); 
    delay(2000);     

    SendData(0x0a); 
    SendData(0x03); 
    SendData(0x0b); 
}

static lv_obj_t *g_kb_screen;
static void kb_screen_event_cb(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *kb = lv_event_get_target(e);
    if (code == LV_EVENT_READY || code == LV_EVENT_CANCEL)
    {
        lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN);
    }
}

lv_obj_t *alarm_load()
{
    // Write codes screen
    now_screen = lv_obj_create(NULL);

    // Create keyboard on screen
    lv_obj_t *g_kb_screen = lv_keyboard_create(now_screen);
    lv_obj_add_event_cb(g_kb_screen, kb_screen_event_cb, LV_EVENT_ALL, NULL);
    lv_obj_add_flag(g_kb_screen, LV_OBJ_FLAG_HIDDEN);
    lv_obj_set_style_text_font(g_kb_screen, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_scrollbar_mode(now_screen, LV_SCROLLBAR_MODE_OFF);

    // Set style for screen. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(now_screen, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(now_screen, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(now_screen, LV_GRAD_DIR_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(now_screen, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes screen_label_1
    lv_obj_t *screen_label_1 = lv_label_create(now_screen);
    lv_obj_set_pos(screen_label_1, 140, 44);
    lv_obj_set_size(screen_label_1, 183, 115);
    lv_obj_set_scrollbar_mode(screen_label_1, LV_SCROLLBAR_MODE_OFF);
    lv_label_set_text(screen_label_1, "闹钟已开");
    lv_label_set_long_mode(screen_label_1, LV_LABEL_LONG_WRAP);

    // Set style for screen_label_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(screen_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(screen_label_1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(screen_label_1, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(screen_label_1, LV_GRAD_DIR_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(screen_label_1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(screen_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(screen_label_1, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(screen_label_1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(screen_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_x(screen_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_y(screen_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(screen_label_1, lv_color_make(0xe7, 0x08, 0x08), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(screen_label_1, &lv_chinese_font_24_all, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(screen_label_1, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(screen_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(screen_label_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(screen_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(screen_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(screen_label_1, 44, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(screen_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes screen_btn_1
    lv_obj_t *screen_btn_1 = lv_btn_create(now_screen);
    lv_obj_set_pos(screen_btn_1, 180, 190);
    lv_obj_set_size(screen_btn_1, 118, 66);
    lv_obj_set_scrollbar_mode(screen_btn_1, LV_SCROLLBAR_MODE_OFF);

    // Set style for screen_btn_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(screen_btn_1, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(screen_btn_1, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(screen_btn_1, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(screen_btn_1, LV_GRAD_DIR_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(screen_btn_1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(screen_btn_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(screen_btn_1, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(screen_btn_1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(screen_btn_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_x(screen_btn_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_y(screen_btn_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(screen_btn_1, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(screen_btn_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(screen_btn_1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(screen_btn_1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(screen_btn_1, &lv_chinese_font_24_all, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(screen_btn_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_t *screen_btn_1_label = lv_label_create(screen_btn_1);
    lv_label_set_text(screen_btn_1_label, "关闭");
    lv_obj_set_style_pad_all(screen_btn_1, 0, LV_STATE_DEFAULT);
    lv_obj_align(screen_btn_1_label, LV_ALIGN_CENTER, 0, 0);

    lv_obj_add_event_cb(screen_btn_1, alarm_cancel_event, LV_EVENT_CLICKED, NULL);
    music_alarm_change();
    SK6812Loop();
    music_alarm_timer = lv_timer_create(music_alarm_timer_cb, 300, NULL);

    return now_screen;
}

void alarm_cancel_event(lv_event_t *e)
{
    SendData(0x13);
    lv_timer_del(music_alarm_timer);
    SK6812Stop();
    app_return(LV_SCR_LOAD_ANIM_MOVE_RIGHT, 200, 20);
}

void music_alarm_change()
{
    if (music_choose_flag == 0)
    {
        show_number1();
    }
    else if (music_choose_flag == 1)
    {
        show_number2();
    }
    else if (music_choose_flag == 2)
    {
        show_number3();
    }

    Serial.println("THIS IS THE TIMER");
}

void music_alarm_timer_cb(lv_timer_t *timer)
{
    SK6812Loop();
}