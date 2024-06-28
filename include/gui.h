/*
 * @Author: JaspinXu sea.xuo@gmail.com
 * @Date: 2024-05-04 10:32:52
 * @LastEditors: JaspinXu sea.xuo@gmail.com
 * @LastEditTime: 2024-06-17 22:09:02
 * @FilePath: \Software\include\gui.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#ifndef GUI_H
#define GUI_H
#include "driver/lv_port_indev.h"
#include "lvgl.h"
#include "head.h"
#include "app/home/home.h"
#include "app/bilibili/bilibili.h"

extern bool use_lvgl;  //使用lvgl
/**
 * @brief load 是一个函数指针类型，
 * 它指向一个返回类型为 lv_obj_t* 的函数，该函数不接受任何参数。
 * 
 */
typedef lv_obj_t* (*load)();
enum MODE       //枚举类型，是app中的各组件ui
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
extern bool RUNMODE;  //运行模式
extern lv_obj_t* now_screen;   //目前屏幕
extern bool MODE_revise;    //修改运行模式
void null_func();        
void gui_init(uint8_t runMODE=HOME);      //gui初始化默认为home
void app_open(load app_load,lv_scr_load_anim_t anim_type, uint32_t time, uint32_t delay, bool auto_del=true,void (*Other_app)()=NULL);
void app_return(lv_scr_load_anim_t anim_type, uint32_t time, uint32_t delay, bool auto_del=true);//屏幕返回的变量
void gesture(bool top,bool bottom,bool left,bool right,void(*back_task)()=null_func);
#endif

