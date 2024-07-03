#ifndef GUI_H
#define GUI_H
#include "driver/lv_port_indev.h"
#include "lvgl.h"
#include "head.h"
#include "app/home/home.h"
#include "app/bilibili/bilibili.h"

extern bool use_lvgl; 
typedef lv_obj_t* (*load)();
enum MODE  
{
    HOME=0,
    TIME,
    WEATHER,
    CALENDAR,
    BILIBILI,
    CALCULATOR,
    SETTING,
    MENU,
    CONPANEL,
};
extern bool RUNMODE;  
extern lv_obj_t* now_screen; 
extern bool MODE_revise; 
void null_func();        
void gui_init(uint8_t runMODE=HOME);  
void app_open(load app_load,lv_scr_load_anim_t anim_type, uint32_t time, uint32_t delay, bool auto_del=true,void (*Other_app)()=NULL);
void app_return(lv_scr_load_anim_t anim_type, uint32_t time, uint32_t delay, bool auto_del=true);
void gesture(bool top,bool bottom,bool left,bool right,void(*back_task)()=null_func);
#endif

