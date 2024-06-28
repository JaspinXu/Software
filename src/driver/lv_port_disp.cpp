/*
 * @Author: JaspinXu sea.xuo@gmail.com
 * @Date: 2024-05-04 10:32:54
 * @LastEditors: JaspinXu sea.xuo@gmail.com
 * @LastEditTime: 2024-06-28 22:26:59
 * @FilePath: \Software\src\driver\lv_port_disp.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
/**
 * @file lv_port_disp.cpp
 *
 */

#if 1

/*********************
 *      INCLUDES
 *********************/
#include "lv_port_disp.h"
#include "../../lib/lvgl/lvgl.h"
#include "common.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void disp_init(void);
bool tft_output(int16_t x, int16_t y, uint16_t w, uint16_t h, uint16_t* bitmap);

static void disp_flush(lv_disp_drv_t * disp_drv, const lv_area_t * area, lv_color_t * color_p);

/**********************
 *  STATIC VARIABLES
 **********************/

#define BUF_MODE 3 //模式选择
//模式1，单缓存
//模式2，双缓存
//模式3，PSRAM双缓存
//模式4，DMA+PSRAM

lv_disp_draw_buf_t draw_buf;

#if (BUF_MODE == 1)
    #define COLOR_BUF_SIZE screenWidth*20
    lv_color_t buf[COLOR_BUF_SIZE] ;

#elif (BUF_MODE == 2)
    #define COLOR_BUF_SIZE screenWidth*20
    DMA_ATTR lv_color_t buf[COLOR_BUF_SIZE] ;
    DMA_ATTR lv_color_t buf2[ COLOR_BUF_SIZE ];
#elif(BUF_MODE == 3)
    #define COLOR_BUF_SIZE 480*320
    lv_color_t *ext_color_buf;
    lv_color_t *ext_color_buf2;
#elif(BUF_MODE == 4)   
    #define COLOR_BUF_SIZE TFT_WIDTH*TFT_HEIGHT/4
    lv_color_t *ext_color_buf;
    lv_color_t *ext_color_buf2;
#endif
/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void lv_port_disp_init(void)
{
    disp_init();

#if (BUF_MODE == 1)
    lv_disp_draw_buf_init( &draw_buf, buf, NULL, COLOR_BUF_SIZE );  //单缓冲
#elif (BUF_MODE == 2)
    lv_disp_draw_buf_init( &draw_buf, buf, buf2, COLOR_BUF_SIZE );  //双缓冲
#elif(BUF_MODE == 3 || BUF_MODE == 4)
    LV_LOG_USER("befor:ESP.getFreeHeap()：%d,PSRAM=%d,Free_PSRAM=%d",ESP.getFreeHeap(),ESP.getPsramSize(),ESP.getFreePsram());

    ext_color_buf = (lv_color_t*)heap_caps_malloc(COLOR_BUF_SIZE*2, MALLOC_CAP_SPIRAM);
    ext_color_buf2 = (lv_color_t*)heap_caps_malloc(COLOR_BUF_SIZE*2, MALLOC_CAP_SPIRAM);
    lv_disp_draw_buf_init( &draw_buf, ext_color_buf, ext_color_buf2, COLOR_BUF_SIZE ); //使用外部PSRAM
    LV_LOG_USER("ext_color_buf：%d,ext_color_buf2=%d",ext_color_buf,ext_color_buf2);
    LV_LOG_USER("after malloc:ESP.getFreeHeap()：%d,PSRAM=%d,Free_PSRAM=%d",ESP.getFreeHeap(),ESP.getPsramSize(),ESP.getFreePsram());

#endif

    /*Initialize the display*/
    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init( &disp_drv );
    /*Change the following line to your display resolution*/
    disp_drv.hor_res = 480;
    disp_drv.ver_res = 320;
    disp_drv.flush_cb = disp_flush;
    disp_drv.draw_buf = &draw_buf;
    lv_disp_drv_register( &disp_drv );
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

/*Initialize your display and the required peripherals.*/
static void disp_init(void)
{
    
}

/*Flush the content of the internal buffer the specific area on the display
 *You can use DMA or any hardware acceleration to do this operation in the background but
 *'lv_disp_flush_ready()' has to be called when finished.*/
static void disp_flush(lv_disp_drv_t * disp_drv, const lv_area_t * area, lv_color_t * color_p)
{
    //  *Inform the graphics library that you are ready with the flushing*/
    uint32_t dt_start = micros();

    uint32_t w = ( area->x2 - area->x1 + 1 );
    uint32_t h = ( area->y2 - area->y1 + 1 );

    tft.startWrite();
    tft.setAddrWindow( area->x1, area->y1, w, h );
    tft.pushColors( ( uint16_t * )&color_p->full, w * h, true );
    tft.endWrite();
    lv_disp_flush_ready( disp_drv );
    uint32_t dt_interval = micros() - dt_start;
}

#else /*Enable this file at the top*/
#endif
