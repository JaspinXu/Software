#ifndef __SK6812_H_
#define __SK6812_H_

#ifdef __cplusplus
extern "C" {
#endif

#ifndef BRIGHTNESS  
#define BRIGHTNESS  50
#endif

#ifndef LED_TYPE   
#define LED_TYPE    SK6812
#endif

#ifndef COLOR_ORDER 
#define COLOR_ORDER GRB
#endif

#ifndef UPDATES_PER_SECOND 
#define UPDATES_PER_SECOND 100
#endif

#include "common.h"
#include <Arduino.h>

void SK6812Loop();
void SK6812Init();
void ChangePalettePeriodically();
void FillLEDsFromPaletteColors( uint8_t colorIndex);
void SetupPurpleAndGreenPalette();
void SetupBlackAndWhiteStripedPalette();
void SetupTotallyRandomPalette();

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
