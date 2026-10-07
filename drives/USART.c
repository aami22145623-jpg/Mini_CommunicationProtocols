/*
 * USART.c
 *
 *  Created on: 13 Feb 2023
 *      Author: Alaa Wahba
 */

#include "inc/USART.h"
#include <avr/io.h>
#include <stdio.h>

#define Default_Stop '\r'

static uint32 flag = 1;
static uint8 *TX_str;


/*
 * USART Initialization
 */
void USART_init(UART_Config_t *pinConfig)
{
    uint16 ubrr;

    /* ================= Baud Rate ================= */

    /*
     * Normal asynchronous mode
     *
     * Baud Rate = F_CPU / (16 * (UBRR + 1))
     *
     * For:
     * F_CPU = 16 MHz
     * Baud Rate = 9600
     *
     * UBRR = 103
     */

    ubrr = (F_CPU / (16UL * pinConfig->baudRate)) - 1;

    UBRRH = (uint8)(ubrr >> 8);
    UBRRL = (uint8)ubrr;


    /* ================= FRAME ================= */

    /*
     * Asynchronous mode
     *
     * UCSRC:
     *
     * URSEL = 1
     * UMSEL = 0 -> Asynchronous
     * UPM1:0 = 00 -> No parity
     * USBS = 0 -> 1 Stop bit
     * UCSZ1:0 = 11
     * UCSZ2 = 0 -> 8 Data bits
     */

    UCSRC = (1 << URSEL) |
            (1 << UCSZ1) |
            (1 << UCSZ0);


    /* ================= Enable ================= */

    /*
     * Enable Receiver
     * Enable Transmitter
     */

    UCSRB = (1 << RXEN) |
            (1 << TXEN);
}


/*
 * Send one byte
 */
void USART_send(uint8 data)
{
    /*
     * Wait until transmit buffer is empty
     */
    while (!(UCSRA & (1 << UDRE)))
        ;

    /*
     * Put data into transmit buffer
     */
    UDR = data;
}


/*
 * Receive one byte
 */
uint8 USART_recieve()
{
    /*
     * Wait until data is received
     */
    while (!(UCSRA & (1 << RXC)))
        ;

    /*
     * Return received data
     */
    return UDR;
}


/*
 * Send Number
 */
void USART_sendNumber(uint32 data)
{
    char str[11];

    sprintf(str, "%lu", (unsigned long)data);

    USART_sendString((uint8 *)str);
}


/*
 * Receive Number
 */
uint32 USART_recieveNumber()
{
    uint32 num = 0;
    uint8 data;

    do
    {
        data = USART_recieve();

        if (data >= '0' && data <= '9')
        {
            num = (num * 10) + (data - '0');
        }

    } while (data != Default_Stop);

    return num;
}


/*
 * Send String
 */
void USART_sendString(uint8 *str)
{
    uint8 i = 0;

    /*
     * Continue until NULL character
     */
    while (str[i] != '\0')
    {
        USART_send(str[i]);
        i++;
    }

    /*
     * End of string
     */
    USART_send(Default_Stop);
}


/*
 * Receive String
 */
void USART_recieveString(uint8 *Buff)
{
    uint8 i = 0;

    Buff[i] = USART_recieve();

    while (Buff[i] != Default_Stop)
    {
        i++;

        Buff[i] = USART_recieve();
    }

    /*
     * Replace '\r' with NULL
     */
    Buff[i] = '\0';
}