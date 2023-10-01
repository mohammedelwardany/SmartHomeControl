/*
 * UART_cfg.h
 *
 *  Created on: Sep 22, 2023
 *      Author: Emii
 */

#ifndef MCAL_UART_V1_UART_CFG_H_
#define MCAL_UART_V1_UART_CFG_H_

#define F_OSC                            16000000

#define MODE_SPEED                       ASYNCHROUNUS_NORMAL_SPEED
#define BAUD_RATE                        9600

#define PARITY                           NO_PARITY //(EVEN-ODD)
#define DATA_SIZE                        8
#define STOP_BITS                        1

#define TRANSMISIION_MODE                TRANSIVER

/*The UCPOL bit sets the relationship between data output change and
data input sample, and the synchronous clock (XCK)*/
//Select Either TX_CHANGED_ON_RISING_RX_SAMPLED_ON_FALLING or TX_CHANGED_ON_FALLING_RX_SAMPLED_ON_RISING
#define CLOCK_POLARITY		TX_CHANGED_ON_RISING_RX_SAMPLED_ON_FALLING

/*
 * Operating Mode                |  Equation for Calculating    |   Equation for Calculating
 *                               |        Baud Rate             |           UBRR Value
 *                               |                              |
Asynchronous Normal Mode         |  BAUD= fOSC/16(UBRR + 1)     |   UBRR = (fOSC/16*BAUD)-1
(U2X = 0)                        |                              |
                                 |                              |
Asynchronous Double Speed Mode   |   BAUD= fOSC/8(UBRR + 1)     |   UBRR = (fOSC/8*BAUD)-1
(U2X = 1)                        |                              |
                                 |                              |
Synchronous Master Mode          |   BAUD= fOSC/2(UBRR + 1)     |   UBRR = (fOSC/2*BAUD)-1
 */

#endif /* MCAL_UART_V1_UART_CFG_H_ */
