#include <Arduino.h>
#include <WiFi.h>
#include "wifiscan.h"

void wifi_init(){
  WiFi.mode(WIFI_STA); 
  WiFi.disconnect(); 
  delay(100);
}

void wifi_begin()
{
  WiFi.begin("JaspinXu" , "xu20040716");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.print("...");
  }
  Serial.println("");
  Serial.println("WiFi Connected!");
}

void wifi_stop()
{
  WiFi.disconnect(true,false);
}
