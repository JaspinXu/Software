/*
 * @Author: JaspinXu sea.xuo@gmail.com
 * @Date: 2024-05-04 10:32:54
 * @LastEditors: JaspinXu sea.xuo@gmail.com
 * @LastEditTime: 2024-06-17 23:02:41
 * @FilePath: \Software\src\main.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include "head.h"

const char *ssid = "JaspinXu";
const char *password = "xu20040716";

TFT_eSPI tft = TFT_eSPI();

void setup()
{
  Serial.begin(115200); 
  lv_init();
  tft.begin();      
  tft.setRotation(3); 
  lv_port_disp_init();
  lv_port_indev_init(); 
  WiFi.begin(ssid, password);
  pinMode(music_pin,OUTPUT);
  gui_init();
}

void loop()
{
  lv_timer_handler(); 
  delay(5);
}


