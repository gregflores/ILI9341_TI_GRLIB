/* --COPYRIGHT--,BSD
 * Copyright (c) 2016, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * --/COPYRIGHT--*/
/* DriverLib Includes */
#include "driverlib.h"

/* Standard Includes */
#include <stdint.h>

/* GrLib Includes */
#include "grlib.h"

#include "LcdDriver/kitronix320x240x16_ssd2119_spi.h"
#include "images/images.h"

// Graphic library context
Graphics_Context g_sContext;

//Flag to know if a demo was run
bool g_ranDemo = false;

void Delay(uint16_t msec);
void boardInit(void);
void clockInit(void);

void drawMainMenu(void);
void runPrimitivesDemo(void);
void runImagesDemo(void);
void drawRestarDemo(void);

void main(void)
{
//	int16_t ulIdx;
    WDT_A_hold(WDT_A_BASE);

    /* Initialize the demo. */
    boardInit();
    clockInit();


    /* Globally enable interrupts. */
    __enable_interrupt();

    // LCD setup using Graphics Library API calls
    Kitronix320x240x16_SSD2119Init();
    Graphics_initContext(&g_sContext, &g_sKitronix320x240x16_SSD2119);
    Graphics_setBackgroundColor(&g_sContext, GRAPHICS_COLOR_BLACK);
    Graphics_setFont(&g_sContext, &g_sFontCmss20b);
    Graphics_clearDisplay(&g_sContext);

    drawMainMenu();

    // Loop to detect touch
    while(1)
    {



    }
}


void drawMainMenu(void)
{
    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_RED);
    Graphics_setBackgroundColor(&g_sContext, GRAPHICS_COLOR_BLACK);
    Graphics_clearDisplay(&g_sContext);
    Graphics_drawStringCentered(&g_sContext, "MSP Graphics Library Demo",
                                AUTO_STRING_LENGTH,
                                159,
                                15,
                                TRANSPARENT_TEXT);

    // Draw TI banner at the bottom of screnn
    Graphics_drawImage(&g_sContext,
                       &TI_platform_bar_red4BPP_UNCOMP,
                       0,
                       Graphics_getDisplayHeight(
                           &g_sContext) - TI_platform_bar_red4BPP_UNCOMP.ySize);

}

void runPrimitivesDemo(void)
{
    int16_t ulIdx;
    uint32_t color;

    Graphics_Rectangle myRectangle1 = { 10, 50, 155, 120};
    Graphics_Rectangle myRectangle2 = { 150, 100, 300, 200};
    Graphics_Rectangle myRectangle3 = { 0, 0, 319, 239};

    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_RED);
    Graphics_setBackgroundColor(&g_sContext, GRAPHICS_COLOR_BLACK);
    Graphics_clearDisplay(&g_sContext);
    Graphics_drawString(&g_sContext, "Draw Pixels & Lines", AUTO_STRING_LENGTH,
                        60, 5, TRANSPARENT_TEXT);
    Graphics_drawPixel(&g_sContext, 45, 45);
    Graphics_drawPixel(&g_sContext, 45, 50);
    Graphics_drawPixel(&g_sContext, 50, 50);
    Graphics_drawPixel(&g_sContext, 50, 45);
    Graphics_drawLine(&g_sContext, 60, 60, 200, 200);
    Graphics_drawLine(&g_sContext, 30, 200, 200, 60);
    Graphics_drawLine(&g_sContext, 0, Graphics_getDisplayHeight(
                          &g_sContext) - 1,
                      Graphics_getDisplayWidth(&g_sContext) - 1,
                      Graphics_getDisplayHeight(&g_sContext) - 1);
    Delay(2000);
    Graphics_clearDisplay(&g_sContext);
    Graphics_drawStringCentered(&g_sContext, "Draw Rectangles",
                                AUTO_STRING_LENGTH, 159, 15, TRANSPARENT_TEXT);
    Graphics_drawRectangle(&g_sContext, &myRectangle1);
    Graphics_fillRectangle(&g_sContext, &myRectangle2);
    // Text won't be visible on screen due to transparency (foreground colors match)
    Graphics_drawStringCentered(&g_sContext, "Normal Text", AUTO_STRING_LENGTH,
                                225, 120, TRANSPARENT_TEXT);
    // Text draws foreground and background for opacity
    Graphics_drawStringCentered(&g_sContext, "Opaque Text", AUTO_STRING_LENGTH,
                                225, 150, OPAQUE_TEXT);
    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_BLACK);

    Graphics_setBackgroundColor(&g_sContext, GRAPHICS_COLOR_RED);
    // Text draws with inverted foreground color to become visible
    Graphics_drawStringCentered(&g_sContext, "Invert Text", AUTO_STRING_LENGTH,
                                225, 180, TRANSPARENT_TEXT);
    Delay(2000);
    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_RED);
    Graphics_setBackgroundColor(&g_sContext, GRAPHICS_COLOR_BLACK);
    // Invert the foreground and background colors
    Graphics_fillRectangle(&g_sContext, &myRectangle3);
    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_BLACK);
    Graphics_setBackgroundColor(&g_sContext, GRAPHICS_COLOR_RED);
    Graphics_drawStringCentered(&g_sContext, "Invert Colors",
                                AUTO_STRING_LENGTH, 159, 15, TRANSPARENT_TEXT);
    Graphics_drawRectangle(&g_sContext, &myRectangle1);
    Graphics_fillRectangle(&g_sContext, &myRectangle2);
    // Text won't be visible on screen due to transparency
    Graphics_drawStringCentered(&g_sContext, "Normal Text", AUTO_STRING_LENGTH,
                                225, 120, TRANSPARENT_TEXT);
    // Text draws foreground and background for opacity
    Graphics_drawStringCentered(&g_sContext, "Opaque Text", AUTO_STRING_LENGTH,
                                225, 150, OPAQUE_TEXT);
    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_RED);
    Graphics_setBackgroundColor(&g_sContext, GRAPHICS_COLOR_BLACK);
    // Text draws with inverted color to become visible
    Graphics_drawStringCentered(&g_sContext, "Invert Text", AUTO_STRING_LENGTH,
                                225, 180, TRANSPARENT_TEXT);
    Delay(2000);
    Graphics_clearDisplay(&g_sContext);
    Graphics_drawStringCentered(&g_sContext, "Draw Circles", AUTO_STRING_LENGTH,
                                159, 15, TRANSPARENT_TEXT);
    Graphics_drawCircle(&g_sContext, 100, 100, 50);
    Graphics_fillCircle(&g_sContext, 200, 140, 70);
    Delay(2000);
    Graphics_clearDisplay(&g_sContext);
    // Add some more color
    Graphics_setForegroundColor(&g_sContext, ClrLawnGreen);
    Graphics_setBackgroundColor(&g_sContext, ClrBlack);
    Graphics_clearDisplay(&g_sContext);
    Graphics_drawStringCentered(&g_sContext, "Rainbow of Colored Lines",
                                AUTO_STRING_LENGTH, 159, 15, TRANSPARENT_TEXT);
    // Draw a quarter rectangle sweep of lines from red to purple.
    for(ulIdx = 128; ulIdx >= 1; ulIdx--)
    {
        // Red Color
        *((uint16_t*) (&color) + 1) = 255;
        // Blue and Green Colors
        *((uint16_t*) (&color)) =
            ((((128 - ulIdx) * 255) >> 7) << ClrBlueShift);

        Graphics_setForegroundColor(&g_sContext, color);
        Graphics_drawLine(&g_sContext, 160, 200, 32, ulIdx + 72);
    }
    // Draw a quarter rectangle sweep of lines from purple to blue.
    for(ulIdx = 128; ulIdx >= 1; ulIdx--)
    {
        // Red Color
        *((uint16_t*) (&color) + 1) = (ulIdx * 255) >> 7;
        // Blue and Green Colors
        *((uint16_t*) (&color)) = 255 << ClrBlueShift;

        Graphics_setForegroundColor(&g_sContext, color);
        Graphics_drawLine(&g_sContext, 160, 200, 160 - ulIdx, 72);
    }
    // Clear Red Color
    *((uint16_t*) (&color) + 1) = 0;
    // Draw a quarter rectangle sweep of lines from blue to teal.
    for(ulIdx = 128; ulIdx >= 1; ulIdx--)
    {
        // Blue and Green Colors
        *((uint16_t*) (&color)) =
            ((((128 -
                ulIdx) * 255) >> 7) << ClrGreenShift) | (255 << ClrBlueShift);

        Graphics_setForegroundColor(&g_sContext, color);
        Graphics_drawLine(&g_sContext, 160, 200, 288 - ulIdx, 72);
    }
    // Draw a quarter rectangle sweep of lines from teal to green.
    for(ulIdx = 128; ulIdx >= 0; ulIdx--)
    {
        // Blue and Green Colors
        *((uint16_t*) (&color)) =
            (255 << ClrGreenShift) | (((ulIdx * 255) >> 7) << ClrBlueShift);

        Graphics_setForegroundColor(&g_sContext, color);
        Graphics_drawLine(&g_sContext, 160, 200, 288, 200 - (ulIdx));
    }
    Delay(2000);
    g_ranDemo = true;

    drawRestarDemo();
}

void runImagesDemo(void)
{
    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_RED);
    Graphics_setBackgroundColor(&g_sContext, GRAPHICS_COLOR_BLACK);
    Graphics_clearDisplay(&g_sContext);
    Graphics_drawStringCentered(&g_sContext, "Draw Uncompressed Image",
                                AUTO_STRING_LENGTH, 159, 200, TRANSPARENT_TEXT);
    Delay(2000);
    // Draw Image on the display
    Graphics_drawImage(&g_sContext, &lcd_color_320x2408BPP_UNCOMP, 0, 0);
    Delay(2000);
    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_BLACK);
    Graphics_setBackgroundColor(&g_sContext, GRAPHICS_COLOR_WHITE);
    Graphics_clearDisplay(&g_sContext);
    Graphics_drawStringCentered(&g_sContext, "Draw RLE4 compressed Image",
                                AUTO_STRING_LENGTH, 159, 200, TRANSPARENT_TEXT);
    Delay(2000);
    Graphics_drawImage(&g_sContext, &TI_logo_150x1501BPP_COMP_RLE4, 85, 45);
    Delay(2000);

    g_ranDemo = true;

    drawRestarDemo();
}

void drawRestarDemo(void)
{
    g_ranDemo = false;
    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_RED);
    Graphics_setBackgroundColor(&g_sContext, GRAPHICS_COLOR_BLACK);
    Graphics_clearDisplay(&g_sContext);
    Graphics_drawStringCentered(&g_sContext, "Would you like to go back",
                                AUTO_STRING_LENGTH,
                                159,
                                45,
                                TRANSPARENT_TEXT);
    Graphics_drawStringCentered(&g_sContext, "to the main menu?",
                                AUTO_STRING_LENGTH,
                                159,
                                65,
                                TRANSPARENT_TEXT);





    g_ranDemo = true;
    Delay(1000);
}

void boardInit()
{
    FPU_enableModule();
}

void clockInit(void)
{
    /* 2 flash wait states, VCORE = 1, running off DC-DC, 48 MHz */
    FlashCtl_setWaitState(FLASH_BANK0, 2);
    FlashCtl_setWaitState(FLASH_BANK1, 2);
    PCM_setPowerState(PCM_AM_DCDC_VCORE1);
    CS_setDCOCenteredFrequency(CS_DCO_FREQUENCY_48);
    CS_setDCOFrequency(48000000);
    CS_initClockSignal(CS_MCLK, CS_DCOCLK_SELECT, 1);
    CS_initClockSignal(CS_SMCLK, CS_DCOCLK_SELECT, 1);
    CS_initClockSignal(CS_HSMCLK, CS_DCOCLK_SELECT, 1);

    return;
}

void Delay(uint16_t msec){
    uint32_t i = 0;
    uint32_t time = (msec / 1000) * (SYSTEM_CLOCK_SPEED / 15);

    for(i = 0; i < time; i++)
    {
        ;
    }
}
