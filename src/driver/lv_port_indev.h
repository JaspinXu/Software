
/**
 * @file lv_port_indev.h
 *
 */

 /*set this value to "1" to enable content*/
#if 1

#ifndef LV_PORT_INDEV_TEMPL_H
#define LV_PORT_INDEV_TEMPL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "../../lib/lvgl/lvgl.h"

//电容触摸的控制引脚对应定义，or编码器

#define TOUCH_SDA  42
#define TOUCH_SCL  41
#define TOUCH_INT 40
#define TOUCH_RST 39

//触摸范围与屏幕大小相同
#define TOUCH_WIDTH  320
#define TOUCH_HEIGHT 480

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/
extern void lv_port_indev_init(void);
extern lv_indev_t* indev_encoder;

/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*LV_PORT_INDEV_TEMPL_H*/

#endif /*Disable/Enable content*/
