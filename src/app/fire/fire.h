#pragma once

#ifndef BRIGHTNESS  
#define BRIGHTNESS  100
#endif

#ifndef LED_TYPE   
#define LED_TYPE    SK6812
#endif

#ifndef COLOR_ORDER 
#define COLOR_ORDER GRB
#endif

#include "head.h"
#include "common.h"
#include <Arduino.h>
#include <ESP_Mail_Client.h>
#define SMTP_HOST "smtp.qq.com"

#define SMTP_PORT esp_mail_smtp_port_587 // port 465 is not available for Outlook.com

#define AUTHOR_EMAIL "3502093985@qq.com"
#define AUTHOR_PASSWORD "qxqlgitjrzokdbif"
/* Recipient email address */
#define RECIPIENT_EMAIL "1982601931@qq.com"
lv_obj_t *fire_load();
void smtpCallback(SMTP_Status status);
void smtp_init();
void smtpCallback(SMTP_Status status);
void fire_gesture(lv_event_t *e);
void fire_timer_cb(lv_timer_t *timer);

void SK6812Loop();
void SK6812Init();
void SK6812Stop();









