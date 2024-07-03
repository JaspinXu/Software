#if 1

#ifndef LV_PORT_INDEV_TEMPL_H
#define LV_PORT_INDEV_TEMPL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "../../lib/lvgl/lvgl.h"

#define TOUCH_SDA  42
#define TOUCH_SCL  41
#define TOUCH_INT 40
#define TOUCH_RST 39
#define TOUCH_WIDTH  320
#define TOUCH_HEIGHT 480
extern void lv_port_indev_init(void);
extern lv_indev_t* indev_encoder;

#ifdef __cplusplus
} 
#endif
#endif 
#endif 
