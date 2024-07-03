#pragma once
#include "head.h"
#include <ArduinoJson.h> 
#include <HTTPClient.h>

class Bilibili
{
public:
    String UID;
    long fans;
    int follow;
    String name;
    String face;
    uint8_t level;
    String sign;
    int archive_count;
    long likes;
    bool update();

private:
    void ParseData(String url);
    String GitURL(String uid);
};

LV_IMG_DECLARE(bilibili_fans);
LV_IMG_DECLARE(bilibili_likes);
LV_IMG_DECLARE(bilibili_views);
LV_IMG_DECLARE(bilibili_follow);
LV_IMG_DECLARE(bilibili_icon);

extern lv_obj_t*fans_icon;
extern lv_obj_t*like_icon;
extern lv_obj_t*video_icon;
extern lv_obj_t*start_icon;
extern lv_obj_t*fans_num;
extern lv_obj_t*like_num;
extern lv_obj_t*video_num;
extern lv_obj_t*start_num;
extern uint8_t bilibili_theme;
enum
{
    BILIBILI_PINK,
    BILIBILI_BLUE,
};
lv_obj_t* bilibili_load();
lv_obj_t*bilibili_config_load();