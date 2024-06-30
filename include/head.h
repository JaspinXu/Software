/*
 * @Author: JaspinXu sea.xuo@gmail.com
 * @Date: 2024-05-04 10:32:52
 * @LastEditors: JaspinXu sea.xuo@gmail.com
 * @LastEditTime: 2024-06-07 17:23:03
 * @FilePath: \Software\include\head.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#ifndef HEAD_H
#define HEAD_H

#include <lvgl.h>
#include <Arduino.h>
#include <TFT_eSPI.h> // Hardware-specific library
#include <SPI.h>
#include <WiFi.h>
#include <Arduino.h>
#include "driver/lv_port_disp.h"
#include "driver/lv_port_indev.h"
#include <Wire.h>
#include <PubSubClient.h>
#if LV_BUILD_EXAMPLES
/*If you want to use the LVGL examples,
  make sure to install the lv_examples Arduino library
  and uncomment the following line.
  */
#include "examples/lv_examples.h"
#endif

#include "demos/lv_demos.h"
#include "study/myLVGL.h"
#include "study/wifiscan.h"
#include "study/weather.h"
#include "pins_arduino.h"
#include <Arduino.h>
#include <ETH.h>
#include <WiFi.h>
#include <WiFiAP.h>
#include <WiFiClient.h>
#include <WiFiGeneric.h>
#include <WiFiMulti.h>
#include <WiFiSTA.h>
#include <WiFiScan.h>
#include <WiFiServer.h>
#include <WiFiType.h>
#include <WiFiUdp.h>
#include <WiFiClientSecure.h>
#include "esp_wifi.h"
#include <esp_now.h>
#include <SPIFFS.h>
#include <ArduinoJson.h>
#include "bilibili.h"
#include "gui.h"

extern lv_obj_t *setting_title; 
extern void (*other_app)();

LV_FONT_DECLARE(chinese_hei_16);

extern lv_style_t style_chinese_16_white;
extern lv_style_t style_chinese_16_black;

#endif