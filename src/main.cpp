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


