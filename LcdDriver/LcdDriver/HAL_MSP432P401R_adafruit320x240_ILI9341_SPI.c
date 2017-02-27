//*****************************************************************************
//
// HAL_MSP432P401R_adafruit320x240_ILI9341_SPI.c
//
//*****************************************************************************
//
//! \addtogroup display_api
//! @{
//
//*****************************************************************************

#include <LcdDriver/adafruit320x240_ILI9341_spi.h>
#include <LcdDriver/HAL_MSP432P401R_adafruit320x240_ILI9341_SPI.h>
#include "grlib.h"
#include "driverlib.h"

//*****************************************************************************
//
//! Initializes the display driver.
//!
//! This function initializes the Sharp96x96 display. This function
//! configures the GPIO pins used to control the LCD display when the basic
//! GPIO interface is in use. On exit, the LCD has been reset and is ready to
//! receive command and data writes.
//!
//! \return None.
//
//*****************************************************************************
void HAL_LCD_initLCD(void)
{
    //
    // Configure the pins that connect to the LCD as GPIO outputs.
    //
    GPIO_setAsOutputPin(LCD_DC_PORT,
                        LCD_DC_PIN);

    GPIO_setOutputLowOnPin(LCD_DC_PORT,
                           LCD_DC_PIN);

    GPIO_setAsOutputPin(LCD_CS_PORT,
                        LCD_CS_PIN);

    GPIO_setOutputLowOnPin(LCD_CS_PORT,
                           LCD_CS_PIN);

    //
    // Configure SPI peripheral.
    //
    // Configure LCD_MOSI_PIN
    GPIO_setAsPeripheralModuleFunctionOutputPin(LCD_MOSI_PORT,
                                                LCD_MOSI_PIN,
                                                LCD_MOSI_PIN_FUNCTION);

    // Configure LCD_CLK_PIN  option select CLK
    GPIO_setAsPeripheralModuleFunctionOutputPin(LCD_CLK_PORT, 
                                                LCD_CLK_PIN,
                                                LCD_CLK_PIN_FUNCTION);

    eUSCI_SPI_MasterConfig spiMasterConfig =
    {
        EUSCI_B_SPI_CLOCKSOURCE_SMCLK,                      // SMCLK Clock Source
        CS_getSMCLK(),                                  // Get SMCLK frequency
        16000000,                                                // SPICLK = 16 MHz
        EUSCI_B_SPI_MSB_FIRST,                             // MSB First
        EUSCI_B_SPI_PHASE_DATA_CAPTURED_ONFIRST_CHANGED_ON_NEXT,         // Phase
        EUSCI_B_SPI_CLOCKPOLARITY_INACTIVITY_LOW,         // Low polarity
        EUSCI_B_SPI_3PIN                                   // 3Wire SPI Mode
    };

    SPI_initMaster(LCD_EUSCI_MODULE, &spiMasterConfig);

    SPI_clearInterruptFlag(LCD_EUSCI_MODULE,
                           EUSCI_B_SPI_RECEIVE_INTERRUPT);

    SPI_enableModule(LCD_EUSCI_MODULE);

/*    // Initialize USCI_B1 for SPI Master operation
        EUSCI_B_SPI_initMaster(LCD_EUSCI_BASE,
        EUSCI_B_SPI_CLOCKSOURCE_SMCLK,
            CS_getSMCLK(),
            15000000,
        EUSCI_B_SPI_MSB_FIRST,
        EUSCI_B_SPI_PHASE_DATA_CHANGED_ONFIRST_CAPTURED_ON_NEXT,
        EUSCI_B_SPI_CLOCKPOLARITY_INACTIVITY_HIGH,
        EUSCI_B_SPI_3PIN);

    EUSCI_B_SPI_clearInterrupt(LCD_EUSCI_BASE,
                           EUSCI_B_SPI_RECEIVE_INTERRUPT);

    EUSCI_B_SPI_enable(LCD_EUSCI_BASE);*/


    //
    // Set the LCD control pins to their default values.
    //

    GPIO_setOutputHighOnPin(LCD_DC_PORT,
                            LCD_DC_PIN);

    GPIO_setOutputLowOnPin(LCD_CS_PORT,
                           LCD_CS_PIN);

    //
    // Delay for 1ms.
    //
    HAL_LCD_delay(1);
}

//*****************************************************************************
//
// Writes a command to the ILI9341.  This function implements the basic SPI
// interface to the LCD display.
//
//*****************************************************************************
void HAL_LCD_writeCommand(uint8_t command)
{
    //
    // Wait for any SPI transmission to complete before setting the LCD_DC signal.
    //
    while(SPI_isBusy(LCD_EUSCI_MODULE))
    {
        ;
    }

    //
    // Set the LCD_DC signal low, indicating that following writes are commands.
    //
    GPIO_setOutputLowOnPin(LCD_DC_PORT, LCD_DC_PIN);

    //
    // Transmit the command.
    //
    SPI_transmitData(LCD_EUSCI_MODULE, command);

    //
    // Wait for the SPI transmission to complete before setting the LCD_SDC signal.
    //
    while(SPI_isBusy(LCD_EUSCI_MODULE))
    {
        ;
    }

    //
    // Set the LCD_SDC signal high, indicating that following writes are data.
    //
    GPIO_setOutputHighOnPin(LCD_DC_PORT,LCD_DC_PIN);
}

//*****************************************************************************
//
// Writes a data word to the ILI9341.  This function implements the basic SPI
// interface to the LCD display.
//
//*****************************************************************************
void HAL_LCD_writeData(uint16_t data)
{
    uint8_t ui8Data;

    //
    // Calculate the high byte to transmit.
    //
    ui8Data = (uint8_t)(data >> 8);

    //
    // Wait for the transmit buffer to become empty.
    //
    while(!SPI_getInterruptStatus(LCD_EUSCI_MODULE,
                                  EUSCI_B_SPI_TRANSMIT_INTERRUPT))
    {
        ;
    }

    //
    // Transmit the high byte.
    //
    SPI_transmitData(LCD_EUSCI_MODULE,ui8Data);

    //
    // Calculate the low byte to transmit.
    //
    ui8Data = (uint8_t)(data & 0xff);

    //
    // Wait for the transmit buffer to become empty.
    //
    while(!SPI_getInterruptStatus(LCD_EUSCI_MODULE,
                                  EUSCI_B_SPI_TRANSMIT_INTERRUPT))
    {
        ;
    }

    //
    // Transmit the high byte.
    //
    SPI_transmitData(LCD_EUSCI_MODULE,ui8Data);
}

//*****************************************************************************
//
// Clears CS line
//
// This macro allows to clear the Chip Select (CS) line
//
// \return None
//
//*****************************************************************************

void HAL_LCD_selectLCD(){
    //
    // Wait for any SPI transmission to complete before setting the LCD_CS signal.
    //
    while(SPI_isBusy(LCD_EUSCI_MODULE))
    {
        ;
    }

    GPIO_setOutputLowOnPin(LCD_CS_PORT, LCD_CS_PIN);
}

//*****************************************************************************
//
// Set CS line
//
// This macro allows to set the Chip Select (CS) line
//
// \return None
//
//*****************************************************************************

void HAL_LCD_deselectLCD(){
    //
    // Wait for any SPI transmission to complete before setting the LCD_SCS signal.
    //
    while(SPI_isBusy(LCD_EUSCI_MODULE))
    {
        ;
    }

    GPIO_setOutputHighOnPin(LCD_CS_PORT, LCD_CS_PIN);
}

//*****************************************************************************
//
// Generates delay of
//
// \param cycles number of cycles to delay
//
// \return None
//
//*****************************************************************************
void HAL_LCD_delay(uint16_t msec)
{
    uint32_t i = 0;
    uint32_t time = (msec / 1000) * (SYSTEM_CLOCK_SPEED / 15);

    for(i = 0; i < time; i++)
    {
        ;
    }
}

//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//*****************************************************************************
