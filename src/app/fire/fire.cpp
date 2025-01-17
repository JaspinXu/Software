#include "fire.h"
#include "app/music/music.h"
#include <FastLED.h>

#define LED_PIN     13
#define NUM_LEDS    1
#define BRIGHTNESS  100
#define LED_TYPE    SK6812
#define COLOR_ORDER GRB

CRGB leds[NUM_LEDS];

SMTPSession smtp;
double smptFlag;
lv_timer_t *fire_timer;
lv_timer_t *smpt_timer;
static lv_obj_t *g_kb_label_2;
static void kb_label_2_event_cb(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *kb = lv_event_get_target(e);
    if (code == LV_EVENT_READY || code == LV_EVENT_CANCEL)
    {
        lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN);
    }
}

lv_obj_t *fire_load()
{
    smptFlag = 0;
    // Write codes label_2
    now_screen = lv_obj_create(NULL);

    // Create keyboard on label_2
    lv_obj_t *g_kb_label_2 = lv_keyboard_create(now_screen);
    lv_obj_add_event_cb(g_kb_label_2, kb_label_2_event_cb, LV_EVENT_ALL, NULL);
    lv_obj_add_flag(g_kb_label_2, LV_OBJ_FLAG_HIDDEN);
    lv_obj_set_style_text_font(g_kb_label_2, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_scrollbar_mode(now_screen, LV_SCROLLBAR_MODE_OFF);

    // Set style for label_2. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(now_screen, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(now_screen, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(now_screen, LV_GRAD_DIR_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(now_screen, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes label_2_btn_1
    lv_obj_t *label_2_btn_1 = lv_btn_create(now_screen);
    lv_obj_set_pos(label_2_btn_1, 194, 209);
    lv_obj_set_size(label_2_btn_1, 100, 50);
    lv_obj_set_scrollbar_mode(label_2_btn_1, LV_SCROLLBAR_MODE_OFF);

    // Set style for label_2_btn_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(label_2_btn_1, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(label_2_btn_1, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(label_2_btn_1, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(label_2_btn_1, LV_GRAD_DIR_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(label_2_btn_1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(label_2_btn_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(label_2_btn_1, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(label_2_btn_1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(label_2_btn_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_x(label_2_btn_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_y(label_2_btn_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(label_2_btn_1, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(label_2_btn_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(label_2_btn_1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(label_2_btn_1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(label_2_btn_1, &lv_chinese_font_24_all, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(label_2_btn_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_t *label_2_btn_1_label = lv_label_create(label_2_btn_1);
    lv_label_set_text(label_2_btn_1_label, "关闭警报");
    lv_obj_set_style_pad_all(label_2_btn_1, 0, LV_STATE_DEFAULT);
    lv_obj_align(label_2_btn_1_label, LV_ALIGN_CENTER, 0, 0);

    // Write codes label_2_label_3
    lv_obj_t *label_2_label_3 = lv_label_create(now_screen);
    lv_obj_set_pos(label_2_label_3, 83, 122);
    lv_obj_set_size(label_2_label_3, 315, 50);
    lv_obj_set_scrollbar_mode(label_2_label_3, LV_SCROLLBAR_MODE_OFF);
    lv_label_set_text(label_2_label_3, "已经向QQ发送邮件");
    lv_label_set_long_mode(label_2_label_3, LV_LABEL_LONG_WRAP);

    // Set style for label_2_label_3. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(label_2_label_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(label_2_label_3, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(label_2_label_3, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(label_2_label_3, LV_GRAD_DIR_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(label_2_label_3, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(label_2_label_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(label_2_label_3, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(label_2_label_3, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(label_2_label_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_x(label_2_label_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_y(label_2_label_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(label_2_label_3, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(label_2_label_3, &lv_chinese_font_24_all, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(label_2_label_3, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(label_2_label_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(label_2_label_3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(label_2_label_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(label_2_label_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(label_2_label_3, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(label_2_label_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes label_2_label_4
    lv_obj_t *label_2_label_4 = lv_label_create(now_screen);
    lv_obj_set_pos(label_2_label_4, 109, 55);
    lv_obj_set_size(label_2_label_4, 263, 67);
    lv_obj_set_scrollbar_mode(label_2_label_4, LV_SCROLLBAR_MODE_OFF);
    lv_label_set_text(label_2_label_4, "检测到火灾");
    lv_label_set_long_mode(label_2_label_4, LV_LABEL_LONG_WRAP);

    // Set style for label_2_label_4. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(label_2_label_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(label_2_label_4, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(label_2_label_4, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(label_2_label_4, LV_GRAD_DIR_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(label_2_label_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(label_2_label_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(label_2_label_4, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(label_2_label_4, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(label_2_label_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_x(label_2_label_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_y(label_2_label_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(label_2_label_4, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(label_2_label_4, &lv_chinese_font_32_all, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(label_2_label_4, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(label_2_label_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(label_2_label_4, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(label_2_label_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(label_2_label_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(label_2_label_4, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(label_2_label_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_event_cb(label_2_btn_1, fire_gesture, LV_EVENT_LONG_PRESSED, NULL);

    smtp_init();
    show_number2();
    SK6812Loop();
    fire_timer = lv_timer_create(fire_timer_cb, 300, NULL);
    return now_screen;
}

void smtp_init()
{
    /*  Set the network reconnection option */
    MailClient.networkReconnect(true);
    smtp.debug(0);
    smtp.callback(smtpCallback);
    Session_Config config;
    config.server.host_name = SMTP_HOST;
    config.server.port = SMTP_PORT;
    config.login.email = AUTHOR_EMAIL;
    config.login.password = AUTHOR_PASSWORD;
    config.login.user_domain = F("mydomain.net");
    config.time.ntp_server = F("pool.ntp.org,time.nist.gov");
    config.time.gmt_offset = 8;
    config.time.day_light_offset = 0;

    SMTP_Message message;
    message.sender.name = F("ESP32S3");
    message.sender.email = AUTHOR_EMAIL;
    message.subject = F("火灾警报");
    message.addRecipient(F("Master"), RECIPIENT_EMAIL);

    String textMsg = "火灾已发生，请尽快逃离！！！";
    message.text.content = textMsg;
    message.text.charSet = F("us-ascii");
    message.text.transfer_encoding = Content_Transfer_Encoding::enc_7bit;
    message.priority = esp_mail_smtp_priority::esp_mail_smtp_priority_normal;
    message.addHeader(F("Message-ID: <3502093985@qq.com>"));

    if (!smtp.connect(&config))
    {
        return;
    }

    if (!smtp.isLoggedIn())
    {
        Serial.println("\nNot yet logged in.");
    }
    else
    {
        if (smtp.isAuthenticated())
            Serial.println("\nSuccessfully logged in.");
        else
            Serial.println("\nConnected with no Auth.");
    }

    /* Start sending Email and close the session */
    if (!MailClient.sendMail(&smtp, &message))
        smtp.sendingResult.clear();
}

void smtpCallback(SMTP_Status status)
{
    /* Print the current status */
    Serial.println(status.info());
    if (status.success())
    {
        Serial.println("----------------");
        Serial.println("----------------\n");

        for (size_t i = 0; i < smtp.sendingResult.size(); i++)
        {
            /* Get the result item */
            SMTP_Result result = smtp.sendingResult.getItem(i);
        }
        Serial.println("----------------\n");

        smtp.sendingResult.clear();
    }
}

void fire_gesture(lv_event_t *e)
{
    SendData(0x13);
    lv_timer_del(fire_timer);
    SK6812Stop();
    Serial.println("退出警报");
    app_return(LV_SCR_LOAD_ANIM_MOVE_BOTTOM, 200, 20);
}

void fire_timer_cb(lv_timer_t *timer)
{
    SK6812Loop();
}


void SK6812Init() 
{
    delay( 1000 ); 
    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
    FastLED.setBrightness(BRIGHTNESS);
}

void SK6812Loop()
{
    fill_solid(leds, NUM_LEDS, CRGB::Red);
    FastLED.show();
    FastLED.delay(300);
    fill_solid(leds, NUM_LEDS, CRGB::Green);
    FastLED.show();
    FastLED.delay(300);
    fill_solid(leds, NUM_LEDS, CRGB::Blue);
    FastLED.show();
    FastLED.delay(300);
}

void SK6812Stop()
{
    fill_solid(leds, NUM_LEDS, CRGB::Black);
    FastLED.show();
    delay(10);
}
