/*
 * SPI.c
 *
 *  Created on: 22 Feb 2023
 *      Author: Alaa Wahba
 */

#include "inc/SPI.h"
#include <avr/io.h>

void SPI_Init()
{
#ifdef MASTER_MODE

    /* ================= GPIO pins Configuration ================= */

    /*
     * ATmega32 SPI Pins:
     *
     * PB4 -> SS
     * PB5 -> MOSI
     * PB6 -> MISO
     * PB7 -> SCK
     */

    /* SS, MOSI and SCK -> Output */
    DDRB |= (1 << PB4) | (1 << PB5) | (1 << PB7);

    /* MISO -> Input */
    DDRB &= ~(1 << PB6);

    /* Keep SS HIGH */
    PORTB |= (1 << PB4);


    /* ================= Master Configuration ================= */

    /*
     * SPE  -> Enable SPI
     * MSTR -> Master mode
     * SPR0 -> Clock = F_CPU / 16
     */

    SPCR = (1 << SPE) |
           (1 << MSTR) |
           (1 << SPR0);

#endif


#ifdef SLAVE_MODE

    /* ================= GPIO pins Configuration ================= */

    /*
     * PB4 -> SS
     * PB5 -> MOSI
     * PB6 -> MISO
     * PB7 -> SCK
     */

    /* MISO -> Output */
    DDRB |= (1 << PB6);

    /* SS, MOSI and SCK -> Input */
    DDRB &= ~((1 << PB4) |
              (1 << PB5) |
              (1 << PB7));


    /* ================= Slave Configuration ================= */

    /*
     * SPE -> Enable SPI
     */

    SPCR = (1 << SPE);

#endif
}


uint8 SPI_SendRecieveData(uint8 Data)
{
    /* Start transmission */
    SPDR = Data;

    /*
     * Wait until transmission/reception is complete
     *
     * SPIF = SPI Interrupt Flag
     */
    while (!(SPSR & (1 << SPIF)))
    {
        /* Wait */
    }

    /* Return received data */
    return SPDR;
}