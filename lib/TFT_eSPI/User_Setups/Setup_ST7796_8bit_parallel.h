
#define USER_SETUP_ID 1000

#define TFT_PARALLEL_8_BIT

#define ST7796_DRIVER

// For ST7735, ST7789 and ILI9341 ONLY, define the colour order IF the blue and red are swapped on your display
// Try ONE option at a time to find the correct colour order for your display

//#define TFT_RGB_ORDER TFT_RGB  // Colour order Red-Green-Blue
#define TFT_RGB_ORDER TFT_BGR  // Colour order Blue-Green-Red

//#define TFT_INVERSION_ON
#define TFT_INVERSION_OFF

#define TFT_WIDTH  320 //一开始用的240*320的屏幕，但是商家没有例程，使用TFT_eSPI库测试不亮，遂改成320*480
#define TFT_HEIGHT 480

// ESP32 S3 pins used for the parallel interface TFT

#define TFT_CS    10
#define TFT_DC    9 
#define TFT_RST  14

#define TFT_WR    15  
#define TFT_RD    6

#define TFT_D0   1 
#define TFT_D1   2 
#define TFT_D2   7
#define TFT_D3   8
#define TFT_D4   3 
#define TFT_D5   18
#define TFT_D6   17
#define TFT_D7   16

#define TFT_BL   4      
#define TFT_BACKLIGHT_ON LOW  //低电平有效


#define LOAD_GLCD
#define LOAD_FONT2
#define LOAD_FONT4
#define LOAD_FONT6
#define LOAD_FONT7
#define LOAD_FONT8
#define LOAD_GFXFF

#define SMOOTH_FONT
