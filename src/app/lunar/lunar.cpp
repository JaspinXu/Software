#include "lunar.h"
#include "app/fire/fire.h"
#include <stdio.h>
#include <stdint.h>
#include <math.h>
lv_timer_t *lunar_timer;

typedef struct
{
    uint16_t year;
    uint8_t month;
    uint8_t date;
    uint8_t week;
    uint8_t hour;
    uint8_t minute;
    uint8_t second;
} Solar_t; 

typedef struct
{
    uint8_t has_leap_month; 
    uint8_t leapWhichMonth;    
    uint8_t leapMonthis_30days; 

    uint8_t month;   
    uint8_t is_leap_month; 
    uint8_t date;   
    uint8_t animal;     
    uint8_t tian_gan;  
    uint8_t di_zhi;       
} Lunar_t;          

uint32_t LUNAR_INFO[] = {
    0x04bd8, 0x04ae0, 0x0a570, 0x054d5, 0x0d260, 0x0d950, 0x16554, 0x056a0, 0x09ad0, 0x055d2, // 1900-1909
    0x04ae0, 0x0a5b6, 0x0a4d0, 0x0d250, 0x1d255, 0x0b540, 0x0d6a0, 0x0ada2, 0x095b0, 0x14977, // 1910-1919
    0x04970, 0x0a4b0, 0x0b4b5, 0x06a50, 0x06d40, 0x1ab54, 0x02b60, 0x09570, 0x052f2, 0x04970, // 1920-1929
    0x06566, 0x0d4a0, 0x0ea50, 0x16a95, 0x05ad0, 0x02b60, 0x186e3, 0x092e0, 0x1c8d7, 0x0c950, // 1930-1939
    0x0d4a0, 0x1d8a6, 0x0b550, 0x056a0, 0x1a5b4, 0x025d0, 0x092d0, 0x0d2b2, 0x0a950, 0x0b557, // 1940-1949
    0x06ca0, 0x0b550, 0x15355, 0x04da0, 0x0a5b0, 0x14573, 0x052b0, 0x0a9a8, 0x0e950, 0x06aa0, // 1950-1959
    0x0aea6, 0x0ab50, 0x04b60, 0x0aae4, 0x0a570, 0x05260, 0x0f263, 0x0d950, 0x05b57, 0x056a0, // 1960-1969
    0x096d0, 0x04dd5, 0x04ad0, 0x0a4d0, 0x0d4d4, 0x0d250, 0x0d558, 0x0b540, 0x0b6a0, 0x195a6, // 1970-1979
    0x095b0, 0x049b0, 0x0a974, 0x0a4b0, 0x0b27a, 0x06a50, 0x06d40, 0x0af46, 0x0ab60, 0x09570, // 1980-1989
    0x04af5, 0x04970, 0x064b0, 0x074a3, 0x0ea50, 0x06b58, 0x05ac0, 0x0ab60, 0x096d5, 0x092e0, // 1990-1999
    0x0c960, 0x0d954, 0x0d4a0, 0x0da50, 0x07552, 0x056a0, 0x0abb7, 0x025d0, 0x092d0, 0x0cab5, // 2000-2009
    0x0a950, 0x0b4a0, 0x0baa4, 0x0ad50, 0x055d9, 0x04ba0, 0x0a5b0, 0x15176, 0x052b0, 0x0a930, // 2010-2019
    0x07954, 0x06aa0, 0x0ad50, 0x05b52, 0x04b60, 0x0a6e6, 0x0a4e0, 0x0d260, 0x0ea65, 0x0d530, // 2020-2029
    0x05aa0, 0x076a3, 0x096d0, 0x04afb, 0x04ad0, 0x0a4d0, 0x1d0b6, 0x0d250, 0x0d520, 0x0dd45, // 2030-2039
    0x0b5a0, 0x056d0, 0x055b2, 0x049b0, 0x0a577, 0x0a4b0, 0x0aa50, 0x1b255, 0x06d20, 0x0ada0, // 2040-2049
    0x14b63, 0x09370, 0x049f8, 0x04970, 0x064b0, 0x168a6, 0x0ea50, 0x06aa0, 0x1a6c4, 0x0aae0, // 2050-2059
    0x092e0, 0x0d2e3, 0x0c960, 0x0d557, 0x0d4a0, 0x0da50, 0x05d55, 0x056a0, 0x0a6d0, 0x055d4, // 2060-2069
    0x052d0, 0x0a9b8, 0x0a950, 0x0b4a0, 0x0b6a6, 0x0ad50, 0x055a0, 0x0aba4, 0x0a5b0, 0x052b0, // 2070-2079
    0x0b273, 0x06930, 0x07337, 0x06aa0, 0x0ad50, 0x14b55, 0x04b60, 0x0a570, 0x054e4, 0x0d160, // 2080-2089
    0x0e968, 0x0d520, 0x0daa0, 0x16aa6, 0x056d0, 0x04ae0, 0x0a9d4, 0x0a2d0, 0x0d150, 0x0f252, // 2090-2099
    0x0d520                                                                                   // 2100
};


uint8_t IsLeapYear(uint16_t year)
{
    if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
        return 1; 
    return 0;  
}

uint32_t Calc_Solar_DateInterval(Solar_t *Solar1, Solar_t *Solar2)
{
    int16_t i = 0;
    uint8_t MonthDays[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    uint32_t TotalDays1 = 0;
    uint32_t TotalDays2 = 0; 
    uint32_t TotalDays = 0; 

    MonthDays[1] = (IsLeapYear(Solar1->year) ? 29 : 28);
    for (i = 1; i < Solar1->month; i++)
    {
        TotalDays1 += MonthDays[i - 1]; 
    }
    TotalDays1 += Solar1->date; 

    MonthDays[1] = (IsLeapYear(Solar2->year) ? 29 : 28);
    for (i = 1; i < Solar2->month; i++)
    {
        TotalDays2 += MonthDays[i - 1];
    }
    TotalDays2 += Solar2->date;

    if (Solar1->year == Solar2->year)
    {
        TotalDays = TotalDays2 - TotalDays1;
    }
    else
    {
        for (i = Solar1->year + 1; i < Solar2->year; i++)
        {
            TotalDays += (IsLeapYear(i) ? 366 : 365);
        }
        TotalDays += ((IsLeapYear(Solar1->year) ? 366 : 365) - TotalDays1 + TotalDays2);
    }
    return TotalDays;
}

int8_t Calc_thisLunarYear_HasLeapMonth(uint16_t SolarYear, Lunar_t *Lunar)
{
    if (SolarYear < 1900 || SolarYear > 2100)
        return -1;

    if ((LUNAR_INFO[SolarYear - 1900] & 0x0000000f) == 0 || (LUNAR_INFO[SolarYear - 1900] & 0x0000000f) > 12)
    {
        Lunar->has_leap_month = 0;
        return 0;
    }
    Lunar->has_leap_month = 1;
    Lunar->leapWhichMonth = LUNAR_INFO[SolarYear - 1900] & 0x0000000f;          
    Lunar->leapMonthis_30days = (LUNAR_INFO[SolarYear - 1900] >> 16) & 0x00000001;

    return 1;
}

int8_t Calc_thisLunarMonth_Days(uint16_t SolarYear, uint8_t LunarMonth)
{
    if (SolarYear < 1900 || SolarYear > 2100)
        return -1;
    if (LunarMonth < 1 || LunarMonth > 12)
        return -1;
    if ((LUNAR_INFO[SolarYear - 1900] >> ((12 - LunarMonth) + 4)) & 0x00000001)
    {
        return 30;
    }
    else
    {
        return 29;
    }
}

int8_t Calc_Lunar_From_DateInterval(uint32_t DateInterval, Lunar_t *LU)
{
    uint16_t SolarYear = 1900;
    uint32_t DI_temp = 0;
    int8_t err;

    LU->has_leap_month = 0;
    LU->leapWhichMonth = 0;
    LU->leapMonthis_30days = 0;
    LU->is_leap_month = 0; 
    LU->month = 1;   
    LU->date = 1;
    LU->animal = 1;     
    LU->tian_gan = 7;    
    LU->di_zhi = LU->animal; 

    while (1)
    {
        err = Calc_thisLunarYear_HasLeapMonth(SolarYear, LU);
        if (err == -1)
            return -1; 
        if (LU->is_leap_month == 1)
        {
            DI_temp += LU->leapMonthis_30days ? 30 : 29;
        }
        else 
        {   
            DI_temp += Calc_thisLunarMonth_Days(SolarYear, LU->month);
        }
        if (DI_temp >= DateInterval)
        {
            if (LU->is_leap_month == 1)
            {
                LU->date = (LU->leapMonthis_30days ? 30 : 29) - (DI_temp - DateInterval);
            }
            else
            {
                LU->date = Calc_thisLunarMonth_Days(SolarYear, LU->month) - (DI_temp - DateInterval);
            }
            return 1;
        }

        if ((LU->has_leap_month == 1) && (LU->is_leap_month == 0))
        {

            if (LU->leapWhichMonth == LU->month)
            {
                LU->is_leap_month = 1;
            }
            else
            {
                LU->month += 1;
            }
        }
        else if (((LU->has_leap_month == 1) && (LU->is_leap_month == 1)) || (LU->has_leap_month == 0))
        {
            LU->is_leap_month = 0;
            LU->month += 1;
        }
        if (LU->month > 12)
        {
            if (++SolarYear > 2100)
                return -1;
            LU->month = 1;
            if (++LU->animal > 12)
            {
                LU->animal = 1;
            }
            if (++LU->tian_gan > 10)
            {
                LU->tian_gan = 1;
            }
        }
        LU->di_zhi = LU->animal;
    }
}

int8_t Solar2Lunar(Solar_t *so, Lunar_t *lu)
{
    Solar_t solar_1900;
    solar_1900.year = 1900; 
    solar_1900.month = 1;  
    solar_1900.date = 31; 
    return Calc_Lunar_From_DateInterval(Calc_Solar_DateInterval(&solar_1900, so) + 1, lu);
}

int8_t Calc_24SolarTerms(uint16_t SolarYear, uint8_t *Array_24SolarTermDate)
{
    uint8_t i = 0;
    uint8_t Y = SolarYear % 100; 
    double D = 0.2422;
    double C_20xx[] =
        {
            3.87, 18.73, 5.63, 20.646, 4.81, 20.1,
            5.52, 21.04, 5.678, 21.37, 7.108, 22.83,
            7.5, 23.13, 7.646, 23.042, 8.318, 23.438,
            7.438, 22.36, 7.18, 21.94, 5.4055, 20.12};

    if (SolarYear < 2001 || SolarYear > 2099)
        return -1;

    for (i = 0; i < 24; i++)
    {
        if (i <= 1 || i >= 22)
            Array_24SolarTermDate[i] = ((uint16_t)(Y * D + C_20xx[i])) - ((Y - 1) / 4);
        else
            Array_24SolarTermDate[i] = ((uint16_t)(Y * D + C_20xx[i])) - (Y / 4);
        if (SolarYear == 2026 && i == 1)
        {
            Array_24SolarTermDate[i] -= 1; 
        }
        else if (SolarYear == 2084 && i == 3)
        {
            Array_24SolarTermDate[i] += 1;
        }
        else if (SolarYear == 1911 && i == 6)
        {
            Array_24SolarTermDate[i] += 1;
        }
        else if (SolarYear == 2008 && i == 7)
        {
            Array_24SolarTermDate[i] += 1;
        }
        else if (SolarYear == 1902 && i == 8)
        {
            Array_24SolarTermDate[i] += 1; 
        }
        else if (SolarYear == 1928 && i == 9)
        {
            Array_24SolarTermDate[i] += 1; 
        }
        else if ((SolarYear == 1925 || SolarYear == 2016) && i == 10)
        {
            Array_24SolarTermDate[i] += 1; 
        }
        else if (SolarYear == 1922 && i == 11)
        {
            Array_24SolarTermDate[i] += 1; 
        }
        else if (SolarYear == 2002 && i == 12)
        {
            Array_24SolarTermDate[i] += 1; 
        }
        else if (SolarYear == 1927 && i == 14)
        {
            Array_24SolarTermDate[i] += 1; 
        }
        else if (SolarYear == 1942 && i == 15)
        {
            Array_24SolarTermDate[i] += 1; 
        }
        else if (SolarYear == 2089 && i == 17)
        {
            Array_24SolarTermDate[i] += 1; 
        }
        else if (SolarYear == 2089 && i == 18)
        {
            Array_24SolarTermDate[i] += 1;
        }
        else if (SolarYear == 1978 && i == 19)
        {
            Array_24SolarTermDate[i] += 1; // 例外：1978年的计算结果加1日。
        }
        else if (SolarYear == 1954 && i == 20)
        {
            Array_24SolarTermDate[i] += 1; // 例外：1954年的计算结果加1日。
        }
        else if ((SolarYear == 1918 || SolarYear == 2021) && i == 21)
        {
            Array_24SolarTermDate[i] -= 1; // 例外：1918年和2021年的计算结果减1日。
        }
        else if (SolarYear == 1982 && i == 22)
        {
            Array_24SolarTermDate[i] += 1; // 例外：1982年计算结果加1日，2019年减1日。
        }
        else if (SolarYear == 2019 && i == 22)
        {
            Array_24SolarTermDate[i] -= 1; // 例外：1982年计算结果加1日，2019年减1日。
        }
        else if (SolarYear == 2082 && i == 23)
        {
            Array_24SolarTermDate[i] += 1; // 例外：2082年的计算结果加1日
        }
    }

    return 1;
}

Solar_t solar_1 = {2023, 0};
Lunar_t Lunar_1 = {0};
uint8_t Array_24SoTermDate[12];
static lv_lunar_t lv_lunar;
char tiangan[][4] = {"甲", "乙", "丙", "丁", "戊", "己", "庚", "辛", "壬", "癸"};
char dizhi[][4] = {"子", "丑", "寅", "卯", "辰", "巳", "午", "未", "申", "酉", "戌", "亥"};
char lunar_mon[][8] = {"正月", "二月", "三月", "四月", "五月", "六月", "七月", "八月", "九月", "十月", "冬月", "腊月"};
char lunar_day[][8] = {"初一", "初二", "初三", "初四", "初五", "初六", "初七", "初八", "初九", "初十",
                       "十一", "十二", "十三", "十四", "十五", "十六", "十七", "十八", "十九", "二十",
                       "廿一", "廿二", "廿三", "廿四", "廿五", "廿六", "廿七", "廿八", "廿九", "三十"};
char solarTerms[11][2][8] = {
    {"立春", "雨水"},
    {"惊蛰", "春分"},
    {"清明", "谷雨"},
    {"立夏", "小满"},
    {"芒种", "夏至"},
    {"小暑", "大暑"},
    {"白露", "秋分"},
    {"寒露", "霜降"},
    {"立冬", "小雪"},
    {"大雪", "冬至"},
    {"小寒", "大寒"}};

void lunar_timer_cb(lv_timer_t *timer)
{
    rtc.getDate(&dateStruct);
    solar_1 = {dateStruct.year, dateStruct.month, dateStruct.date, 0};
    int16_t temp = dateStruct.year;
    uint16_t temp16 = dateStruct.year;

    Calc_24SolarTerms(solar_1.year, Array_24SoTermDate);
    Solar2Lunar(&solar_1, &Lunar_1);
    if (timer != NULL && timer->user_data != NULL)
    {
        lv_lunar_t *lunar = (lv_lunar_t *)(timer->user_data);
        uint8_t month;    // 当前农历月份
        uint8_t date;     // 当前农历日
        uint8_t tian_gan; // 1-10甲、乙、丙、丁、戊、己、庚、辛、壬、癸
        uint8_t di_zhi;   
        if (lunar->lunar_year != NULL)
        {

            lv_label_set_text_fmt(lunar->lunar_year, "%s%s", tiangan[Lunar_1.tian_gan - 1], dizhi[Lunar_1.di_zhi - 1]);
        }
        if (lunar->lunar_monthdate != NULL)
        {

            lv_label_set_text_fmt(lunar->lunar_monthdate, "%s%s", lunar_mon[Lunar_1.month - 1], lunar_day[Lunar_1.date - 1]);
        }
        if (lunar->lunar_jieqi != NULL)
        {
            if (solar_1.month == 1)
            {
                if (solar_1.date == Array_24SoTermDate[22])
                {
                    lv_label_set_text_fmt(lunar->lunar_jieqi, "%s", solarTerms[10][0]);
                }
                if (solar_1.date == Array_24SoTermDate[23])
                {
                    lv_label_set_text_fmt(lunar->lunar_jieqi, "%s", solarTerms[10][1]);
                }
                else
                {
                    lv_label_set_text_fmt(lunar->lunar_jieqi, "%s", "");
                }
            }
            else
            {
                if (solar_1.date == Array_24SoTermDate[(solar_1.month - 2) * 2 + 0])
                {
                    lv_label_set_text_fmt(lunar->lunar_jieqi, "%s", solarTerms[solar_1.month - 2][0]);
                }

                if (solar_1.date == Array_24SoTermDate[(solar_1.month - 2) * 2 + 1])
                {
                    lv_label_set_text_fmt(lunar->lunar_jieqi, "%s", solarTerms[solar_1.month - 2][1]);
                }
                else
                {
                    lv_label_set_text_fmt(lunar->lunar_jieqi, "%s", "");
                }
            }
        }
    }
}

lv_obj_t *lunar_load()
{
    // Write codes label_4
    now_screen = lv_obj_create(NULL);

    rtc.getDate(&dateStruct);
    solar_1 = {dateStruct.year, dateStruct.month, dateStruct.date, 0};

    Solar2Lunar(&solar_1, &Lunar_1);
    Serial.println(Lunar_1.animal);
    // Create keyboard on label_4
    lv_obj_t *g_kb_label_4 = lv_keyboard_create(now_screen);
    // lv_obj_add_event_cb(g_kb_label_4, kb_label_4_event_cb, LV_EVENT_ALL, NULL);
    lv_obj_add_flag(g_kb_label_4, LV_OBJ_FLAG_HIDDEN);
    lv_obj_set_style_text_font(g_kb_label_4, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_scrollbar_mode(now_screen, LV_SCROLLBAR_MODE_OFF);

    // Set style for label_4. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(now_screen, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(now_screen, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(now_screen, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(now_screen, LV_GRAD_DIR_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(now_screen, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(now_screen, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(now_screen, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(now_screen, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(now_screen, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_x(now_screen, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_y(now_screen, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(now_screen, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(now_screen, &lv_chinese_font_24_all, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(now_screen, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(now_screen, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(now_screen, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(now_screen, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(now_screen, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(now_screen, 7, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(now_screen, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes label_4_label_1
    lv_obj_t *now_screen_label_1 = lv_label_create(now_screen);
    lv_obj_set_pos(now_screen_label_1, 258, 34);
    lv_obj_set_size(now_screen_label_1, 201, 48);
    lv_obj_set_scrollbar_mode(now_screen_label_1, LV_SCROLLBAR_MODE_OFF);
    lv_label_set_text(now_screen_label_1, "\n\n");
    lv_label_set_long_mode(now_screen_label_1, LV_LABEL_LONG_WRAP);

    // Set style for label_4_label_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(now_screen_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(now_screen_label_1, lv_color_make(0xf7, 0xf7, 0xf7), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(now_screen_label_1, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(now_screen_label_1, LV_GRAD_DIR_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(now_screen_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(now_screen_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(now_screen_label_1, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(now_screen_label_1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(now_screen_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_x(now_screen_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_y(now_screen_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(now_screen_label_1, lv_color_make(0xff, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(now_screen_label_1, &lv_chinese_font_32_all, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(now_screen_label_1, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(now_screen_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(now_screen_label_1, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(now_screen_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(now_screen_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(now_screen_label_1, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(now_screen_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes label_4_img_1
    lv_obj_t *now_screen_img_1 = lv_img_create(now_screen);
    lv_obj_set_pos(now_screen_img_1, 26, 28);
    lv_obj_set_size(now_screen_img_1, 197, 264);
    lv_obj_set_scrollbar_mode(now_screen_img_1, LV_SCROLLBAR_MODE_OFF);

    // Set style for label_4_img_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_img_recolor(now_screen_img_1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(now_screen_img_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(now_screen_img_1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_flag(now_screen_img_1, LV_OBJ_FLAG_CLICKABLE);

    if (Lunar_1.animal == 1)
        lv_img_set_src(now_screen_img_1, &_mouse_alpha_197x264);
    else if (Lunar_1.animal == 2)
        lv_img_set_src(now_screen_img_1, &_ox_alpha_197x264);
    else if (Lunar_1.animal == 3)
        lv_img_set_src(now_screen_img_1, &_tiger_alpha_197x264);
    else if (Lunar_1.animal == 4)
        lv_img_set_src(now_screen_img_1, &_rabbit_alpha_197x264);
    else if (Lunar_1.animal == 12)
        lv_img_set_src(now_screen_img_1, &_pig_alpha_197x264);
    else if (Lunar_1.animal == 6)
        lv_img_set_src(now_screen_img_1, &_snake_alpha_197x264);
    else if (Lunar_1.animal == 7)
        lv_img_set_src(now_screen_img_1, &_horse_alpha_197x264);
    else if (Lunar_1.animal == 8)
        lv_img_set_src(now_screen_img_1, &_sheep_alpha_197x264);
    else if (Lunar_1.animal == 9)
        lv_img_set_src(now_screen_img_1, &_monkey_alpha_197x264);
    else if (Lunar_1.animal == 10)
        lv_img_set_src(now_screen_img_1, &_rooster_alpha_197x264);
    else if (Lunar_1.animal == 11)
        lv_img_set_src(now_screen_img_1, &_dog_alpha_197x264);
    else 
        lv_img_set_src(now_screen_img_1, &_loong_alpha_197x264);

    lv_img_set_pivot(now_screen_img_1, 50, 50);
    lv_img_set_angle(now_screen_img_1, 0);

    // Write codes label_4_label_5
    lv_obj_t *now_screen_label_5 = lv_label_create(now_screen);
    lv_obj_set_pos(now_screen_label_5, 258, 88);
    lv_obj_set_size(now_screen_label_5, 197, 44);
    lv_obj_set_scrollbar_mode(now_screen_label_5, LV_SCROLLBAR_MODE_OFF);
    lv_label_set_text(now_screen_label_5, "\n");
    lv_label_set_long_mode(now_screen_label_5, LV_LABEL_LONG_WRAP);

    // Set style for label_4_label_5. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(now_screen_label_5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(now_screen_label_5, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(now_screen_label_5, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(now_screen_label_5, LV_GRAD_DIR_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(now_screen_label_5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(now_screen_label_5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(now_screen_label_5, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(now_screen_label_5, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(now_screen_label_5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_x(now_screen_label_5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_y(now_screen_label_5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(now_screen_label_5, lv_color_make(0x36, 0xbf, 0xf7), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(now_screen_label_5, &lv_chinese_font_32_all, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(now_screen_label_5, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(now_screen_label_5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(now_screen_label_5, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(now_screen_label_5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(now_screen_label_5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(now_screen_label_5, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(now_screen_label_5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes label_4_label_6
    lv_obj_t *now_screen_label_6 = lv_label_create(now_screen);
    lv_obj_set_pos(now_screen_label_6, 360, 34);
    lv_obj_set_size(now_screen_label_6, 119, 45);
    lv_obj_set_scrollbar_mode(now_screen_label_6, LV_SCROLLBAR_MODE_OFF);
    lv_label_set_text(now_screen_label_6, "\n");
    lv_label_set_long_mode(now_screen_label_6, LV_LABEL_LONG_WRAP);

    // Set style for label_4_label_6. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(now_screen_label_6, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(now_screen_label_6, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(now_screen_label_6, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(now_screen_label_6, LV_GRAD_DIR_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(now_screen_label_6, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(now_screen_label_6, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(now_screen_label_6, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(now_screen_label_6, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(now_screen_label_6, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_x(now_screen_label_6, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_y(now_screen_label_6, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(now_screen_label_6, lv_color_make(0x36, 0xbf, 0xf7), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(now_screen_label_6, &lv_chinese_font_32_all, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(now_screen_label_6, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(now_screen_label_6, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(now_screen_label_6, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(now_screen_label_6, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(now_screen_label_6, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(now_screen_label_6, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(now_screen_label_6, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_add_event_cb(now_screen, gesture_lunar, LV_EVENT_GESTURE, NULL);

    lv_lunar = {now_screen_label_1, now_screen_label_5, now_screen_label_6};

    lunar_timer = lv_timer_create(lunar_timer_cb, 1000, (void *)&lv_lunar);
    
    return now_screen;
}

void gesture_lunar(lv_event_t *event)
{
    lv_indev_wait_release(lv_indev_get_act());
    lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
    if (dir == LV_DIR_LEFT)
    {
        lv_timer_del(lunar_timer);
        app_return(LV_SCR_LOAD_ANIM_MOVE_LEFT, 200, 10);
    }
    else if (dir == LV_DIR_RIGHT)
    {
        lv_timer_del(lunar_timer);
        app_open(home_load, LV_SCR_LOAD_ANIM_MOVE_RIGHT, 200, 10);
    }
    else if (dir == LV_DIR_TOP)
    {
        lv_timer_del(lunar_timer);
        app_return(LV_SCR_LOAD_ANIM_MOVE_TOP, 200, 10);
    }
    else if (dir == LV_DIR_BOTTOM)
    {
        lv_timer_del(lunar_timer);
        app_open(bilibili_load, LV_SCR_LOAD_ANIM_MOVE_BOTTOM, 200, 10);
    }
}
