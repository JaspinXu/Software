#include "bilibili.h"
#include "app/fire/fire.h"
#include "app/lunar/lunar.h"

HTTPClient http;    
String url_bilibili = "";   

bool Bilibili::update()
{
        ParseData(GitURL(UID));
        return true;
}
 
String Bilibili::GitURL(String uid) 
{
  url_bilibili =  "https://api.bilibili.com/x/web-interface/card?mid=497309258";
  return url_bilibili;
}
 
void Bilibili::ParseData(String url)
{  
    DynamicJsonDocument doc(3072); 
    http.begin(url);   
    
    int httpGet = http.GET();   
    if(httpGet > 0)
    {
        if(httpGet == HTTP_CODE_OK)  
        {
            String json = http.getString();   
            deserializeJson(doc, json);  
            
            fans=doc["data"]["card"]["fans"].as<long>();
            face=doc["data"]["card"]["face"].as<String>();
            name=doc["data"]["card"]["name"].as<String>();
            level=doc["data"]["card"]["level_info"]["current_level"].as<uint8_t>();
            follow=doc["data"]["card"]["attention"].as<int>();
            likes=doc["data"]["like_num"].as<long>();
            archive_count=doc["data"]["archive_count"].as<int>();
            sign=doc["data"]["card"]["sign"].as<String>();
        }
    }
    http.end();

}
Bilibili bilibili;


lv_obj_t *bilibili_name;
lv_obj_t *bilibili_sign;
lv_obj_t *fans_num;
lv_obj_t *like_num;
lv_obj_t *video_num;
lv_obj_t *start_num;
lv_obj_t *Bilibili_icon;
lv_obj_t *fans_icon;
lv_obj_t *like_icon;
lv_obj_t *video_icon;
lv_obj_t *start_icon;
uint8_t bilibili_theme;
lv_color_t main_color;
lv_color_t text_color;

lv_timer_t *bilibili_timer;

void gesture_bilibili(lv_event_t *event)
{
    lv_indev_wait_release(lv_indev_get_act());
    lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
    if (dir == LV_DIR_LEFT)
    {
        lv_timer_del(bilibili_timer);
        app_open(fire_load, LV_SCR_LOAD_ANIM_MOVE_LEFT, 200, 10);
    }
    else if (dir == LV_DIR_RIGHT)
    {
        lv_timer_del(bilibili_timer);
        app_open(alarm_load, LV_SCR_LOAD_ANIM_MOVE_RIGHT, 200, 10);
    }
    else if (dir == LV_DIR_TOP)
    {
        lv_timer_del(bilibili_timer);
        app_open(lunar_load,LV_SCR_LOAD_ANIM_MOVE_TOP, 200, 10);
    }
    else if (dir == LV_DIR_BOTTOM)
    {
        lv_timer_del(bilibili_timer);
        app_return(LV_SCR_LOAD_ANIM_MOVE_BOTTOM,200,10);
    }
}

void bilibili_timer_cb(lv_timer_t *timer)
{
    bilibili.update();
    lv_label_set_text(bilibili_name, bilibili.name.c_str());
    lv_label_set_text(bilibili_sign, bilibili.sign.c_str());
    lv_label_set_text(fans_num, String(bilibili.fans).c_str());
    lv_label_set_text(like_num, String(bilibili.likes).c_str());
    lv_label_set_text(video_num, String(bilibili.archive_count).c_str());
    lv_label_set_text(start_num, String(bilibili.follow).c_str());
}

void bilibili_event(lv_event_t *e)
{
    lv_obj_t *target = lv_event_get_target(e);
    lv_event_code_t event_code = lv_event_get_code(e);
    switch (event_code)
    {
    case LV_EVENT_VALUE_CHANGED:
    {
        lv_label_set_text(bilibili_name, bilibili.name.c_str());
        lv_label_set_text(bilibili_sign, bilibili.sign.c_str());
        lv_label_set_text(fans_num, String(bilibili.fans).c_str());
        lv_label_set_text(like_num, String(bilibili.likes).c_str());
        lv_label_set_text(video_num, String(bilibili.archive_count).c_str());
        lv_label_set_text(start_num, String(bilibili.follow).c_str());

        lv_obj_align_to(bilibili_name, Bilibili_icon, LV_ALIGN_OUT_BOTTOM_MID, 0, 0);
        lv_obj_align_to(bilibili_sign, bilibili_name, LV_ALIGN_OUT_BOTTOM_MID, 0, 5);
        lv_obj_align_to(fans_num, fans_icon, LV_ALIGN_OUT_BOTTOM_MID, 0, 5);
        lv_obj_align_to(like_num, like_icon, LV_ALIGN_OUT_BOTTOM_MID, 0, 5);
        lv_obj_align_to(video_num, video_icon, LV_ALIGN_OUT_BOTTOM_MID, 0, 5);
        lv_obj_align_to(start_num, start_icon, LV_ALIGN_OUT_BOTTOM_MID, 0, 5);
    }
    }
}

lv_obj_t *bilibili_load()
{
    now_screen = lv_obj_create(NULL);
    bilibili.update();
    main_color = lv_color_hex(0x98fb98);
    text_color = lv_color_hex(0x191970);
    lv_obj_set_style_bg_color(now_screen, main_color, LV_STATE_DEFAULT);
    lv_obj_set_size(now_screen, 480 , 320);

    Bilibili_icon = lv_img_create(now_screen);
    fans_icon = lv_img_create(now_screen);
    like_icon = lv_img_create(now_screen);
    video_icon = lv_img_create(now_screen);
    start_icon = lv_img_create(now_screen);

    lv_img_set_src(Bilibili_icon, &bilibili_icon);
    lv_img_set_src(fans_icon, &bilibili_fans);
    lv_img_set_src(like_icon, &bilibili_likes);
    lv_img_set_src(video_icon, &bilibili_views);
    lv_img_set_src(start_icon, &bilibili_follow);

    lv_obj_align_to(Bilibili_icon, now_screen, LV_ALIGN_TOP_MID, 0, 30);
    lv_obj_align_to(fans_icon, now_screen, LV_ALIGN_TOP_LEFT, 35, 135);
    lv_obj_align_to(like_icon, now_screen, LV_ALIGN_TOP_RIGHT, -35, 135);
    lv_obj_align_to(video_icon, fans_icon, LV_ALIGN_OUT_BOTTOM_MID, 0, 40);
    lv_obj_align_to(start_icon, like_icon, LV_ALIGN_OUT_BOTTOM_MID, 0, 40);

    bilibili_name = lv_label_create(now_screen);
    bilibili_sign = lv_label_create(now_screen);
    fans_num = lv_label_create(now_screen);
    like_num = lv_label_create(now_screen);
    video_num = lv_label_create(now_screen);
    start_num = lv_label_create(now_screen);

    lv_obj_set_style_text_font(bilibili_name, &chinese_hei_16, 0);
    lv_obj_set_style_text_font(bilibili_sign, &chinese_hei_16, 0);
    lv_obj_set_style_text_color(bilibili_name, text_color, 0);
    lv_obj_set_style_text_color(bilibili_sign, lv_color_make(0, 0, 0), 0);
    lv_obj_set_style_text_color(fans_num, text_color, 0);
    lv_obj_set_style_text_color(like_num, text_color, 0);
    lv_obj_set_style_text_color(video_num, text_color, 0);
    lv_obj_set_style_text_color(start_num, text_color, 0);

    lv_label_set_text(bilibili_name, bilibili.name.c_str());
    lv_label_set_text(bilibili_sign, bilibili.sign.c_str());
    lv_label_set_text(fans_num, String(bilibili.fans).c_str());
    lv_label_set_text(like_num, String(bilibili.likes).c_str());
    lv_label_set_text(video_num, String(bilibili.archive_count).c_str());
    lv_label_set_text(start_num, String(bilibili.follow).c_str());

    lv_obj_align_to(bilibili_name, Bilibili_icon, LV_ALIGN_OUT_BOTTOM_MID, 0, 5);
    lv_obj_align_to(bilibili_sign, bilibili_name, LV_ALIGN_OUT_BOTTOM_MID, 0, 10);
    lv_obj_align_to(fans_num, fans_icon, LV_ALIGN_OUT_BOTTOM_MID, 0, 5);
    lv_obj_align_to(like_num, like_icon, LV_ALIGN_OUT_BOTTOM_MID, 0, 5);
    lv_obj_align_to(video_num, video_icon, LV_ALIGN_OUT_BOTTOM_MID, 0, 5);
    lv_obj_align_to(start_num, start_icon, LV_ALIGN_OUT_BOTTOM_MID, 0, 5);

    lv_obj_add_event_cb(bilibili_name, bilibili_event, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(now_screen, gesture_bilibili, LV_EVENT_GESTURE, NULL);

    bilibili_timer = lv_timer_create(bilibili_timer_cb, 10000, NULL);
    return now_screen;
}

lv_obj_t *UID_text;
lv_obj_t *bilibili_theme_opt;
bool uid_changed = 0;
void UID_change(lv_event_t *e)
{
    int code = lv_event_get_code(e);
    lv_obj_t *target = lv_event_get_target(e);
    lv_obj_t *kb = (lv_obj_t *)lv_event_get_user_data(e);
    if (code == LV_EVENT_FOCUSED)
    {
        uid_changed = 1;
        if (lv_indev_get_type(lv_indev_get_act()) != LV_INDEV_TYPE_KEYPAD)
        {
            lv_keyboard_set_mode(kb, LV_KEYBOARD_MODE_NUMBER);
            lv_textarea_set_accepted_chars(UID_text, "0123456789");
            lv_textarea_set_text(UID_text, bilibili.UID.c_str());
            lv_keyboard_set_textarea(kb, target);
            lv_obj_clear_flag(kb, LV_OBJ_FLAG_HIDDEN);
        }
    }
    else if (code == LV_EVENT_DEFOCUSED)
    {
        lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN);
        lv_indev_reset(NULL, target);
    }
    else if (code == LV_EVENT_CANCEL)
    {
        lv_textarea_set_text(UID_text, bilibili.UID.c_str());
        lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN);
        lv_indev_reset(NULL, target);
    }
}
void bilibili_save_event(lv_event_t *e)
{
    if (uid_changed)
    {
        bilibili.UID = lv_textarea_get_text(UID_text);
        bilibili.name = "加载中";
    }
    if (bilibili_theme != lv_dropdown_get_selected(bilibili_theme_opt))
    {
        bilibili_theme = lv_dropdown_get_selected(bilibili_theme_opt);
        lv_textarea_set_text(UID_text, bilibili.name.c_str());
    }
    app_return(LV_SCR_LOAD_ANIM_MOVE_RIGHT, 200, 50);
}
void bilibili_theme_opt_event(lv_event_t *e)
{
    lv_obj_t *dropdown = lv_event_get_target(e);
    lv_obj_t *list = lv_dropdown_get_list(dropdown);
    if (list != NULL)
    {
        lv_obj_set_style_bg_color(list, lv_color_hex(0xffffff), LV_PART_MAIN);
        lv_obj_add_style(list, &style_chinese_16_black, LV_PART_MAIN);
        lv_obj_set_style_border_color(list, lv_color_hex(0xdddddd), 0);
        lv_obj_set_style_border_opa(list, 255, 0);
        lv_obj_set_style_border_width(list, 2, 0);
    }
}
lv_obj_t *bilibili_config_load()
{
}