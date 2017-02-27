//*****************************************************************************
//
// HAL_MSP432P401R_adafruit320x240_ILI9341_SPI - Prototypes for the
//           adafruit 320x240 ILI9341 LCD display driver.
//
//
//                 MSP432P401R                 ADAFRUIT 320x240 ILI9341
//                -----------------              ------------
//               |     P1.6/UCB0SIMO|---------> |MOSI        |
//            /|\|                  |           |            |
//             | |      P1.5/UCB0CLK|---------> |CLK         |
//             --|RST               |           |            |
//               |              P5.0|---------> |CS          |
//               |              P3.7|---------> |D/C         |
//               |         	        |           |            |
//               |                  |           |            |
//               |                  |           |            |
//               |                  |            ------------
//                ------------------
//****************************************************************************

#ifndef __HAL_MSP432P401R_ADAFRUIT320X240_ILI9341_SPI_H__
#define __HAL_MSP432P401R_ADAFRUIT320X240_ILI9341_SPI_H__

//*****************************************************************************
//
// User Configuration for the LCD Driver
//
//*****************************************************************************
// MCLK FREQUENCY (in Hz)
#define HAL_LCD_MCLK_FREQUENCY      16000000

#define GRLIB_MSP432_MODE           1

// Ports from MSP432 connected to LCD
#define LCD_MOSI_PORT     GPIO_PORT_P1
#define LCD_CLK_PORT      GPIO_PORT_P1
#define LCD_CS_PORT       GPIO_PORT_P5
#define LCD_DC_PORT       GPIO_PORT_P3


// Pins from MSP432 connected to LCD
#define LCD_MOSI_PIN                    GPIO_PIN6
#define LCD_MOSI_PIN_FUNCTION           GPIO_PRIMARY_MODULE_FUNCTION
#define LCD_CLK_PIN                     GPIO_PIN5
#define LCD_CLK_PIN_FUNCTION            GPIO_PRIMARY_MODULE_FUNCTION
#define LCD_CS_PIN                      GPIO_PIN0
#define LCD_DC_PIN                      GPIO_PIN7

// Definition of USCI base address to be used for SPI communication
#define LCD_EUSCI_MODULE                      EUSCI_B0_BASE

//*****************************************************************************
//
// Prototypes for the globals exported by this driver.
//
//*****************************************************************************
extern void HAL_LCD_initLCD(void);
extern void HAL_LCD_writeCommand(uint8_t command);
extern void HAL_LCD_writeData(uint16_t data);
extern void HAL_LCD_delay(uint16_t msec);
extern void HAL_LCD_selectLCD(void);
extern void HAL_LCD_deselectLCD(void);
extern void HAL_LCD_initTimer(uint16_t captureCompareVal);
extern uint16_t HAL_LCD_getTimerCaptureCompare();
extern void HAL_LCD_setTimerDutyCycle(uint16_t dutyCycle);
extern void HAL_LCD_startTimerCounter(void);
extern void HAL_LCD_stopTimerCounter(void);

#endif // __HAL_MSP432P401R_ADAFRUIT320X240_ILI9341_SPI_H__
