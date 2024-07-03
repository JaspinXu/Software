#ifndef HEAD_H
#define HEAD_H

#include <lvgl.h>
#include <Arduino.h>
#include <TFT_eSPI.h>
#include <WiFi.h>
#include <Arduino.h>
#include "driver/lv_port_disp.h"
#include "driver/lv_port_indev.h"
#include <Wire.h>
#include <PubSubClient.h>
#if LV_BUILD_EXAMPLES
#include "examples/lv_examples.h"
#endif

#include "demos/lv_demos.h"
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
#include "app/bilibili/bilibili.h"
#include "gui.h"
#include "app/music/music.h"
#include "app/fire/fire.h"


extern lv_obj_t *setting_title; 
extern void (*other_app)();

LV_FONT_DECLARE(chinese_hei_16);

extern lv_style_t style_chinese_16_white;
extern lv_style_t style_chinese_16_black;

#endif