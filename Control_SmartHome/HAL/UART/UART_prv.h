/*
 * UART_prv.h
 *
 *  Created on: Sep 22, 2023
 *      Author: Emii
 */

#ifndef MCAL_UART_V1_UART_PRV_H_
#define MCAL_UART_V1_UART_PRV_H_

#define UCSRA 	(*((volatile uint8*)0x2B))
/*UCSRA -> • Bit 7 – RXC: USART Receive Complete
 *         • Bit 6 – TXC: USART Transmit Complete
 *         • Bit 5 – UDRE: USART Data Register Empty
 *         • Bit 4 – FE: Frame Error
 *         • Bit 3 – DOR: Data OverRun
 *         • Bit 2 – PE: Parity Error
 *         • Bit 1 – U2X: Double the USART Transmission Speed
 *         • Bit 0 – MPCM: Multi-processor Communication Mode*/
#define UCSRA_RXC     7
#define UCSRA_TXC     6
#define UCSRA_UDRE    5
#define UCSRA_FE      4
#define UCSRA_DOR     3
#define UCSRA_PE      2
#define UCSRA_U2X     1
#define UCSRA_MPCM    0

#define UCSRB 	(*((volatile uint8*)0x2A))
/*UCSRB -> • Bit 7 – RXCIE: RX Complete Interrupt Enable
 *         • Bit 6 – TXCIE: TX Complete Interrupt Enable
 *         • Bit 5 – UDRIE: USART Data Register Empty Interrupt Enable
 *         • Bit 4 – RXEN: Receiver Enable
 *         • Bit 3 – TXEN: Transmitter Enable
 *         • Bit 2 – UCSZ2: Character Size
 *         • Bit 1 – RXB8: Receive Data Bit 8
 *         • Bit 0 – TXB8: Transmit Data Bit 8*/
#define UCSRB_TXB8       0
#define UCSRB_RXB8		 1
#define UCSRB_UCSZ2		 2
#define UCSRB_TXEN		 3
#define UCSRB_RXEN		 4
#define UCSRB_UDRIE		 5
#define UCSRB_TXCIE		 6
#define UCSRB_RXCIE		 7


#define UCSRC 	(*((volatile uint8*)0x40))
/*UCSRC -> • Bit 7 – URSEL: Register Select
 *         • Bit 6 – UMSEL: USART Mode Select
 *         • Bit 5:4 – UPM1:0: Parity Mode
 *         • Bit 3 – USBS: Stop Bit Select
 *         • Bit 2:1 – UCSZ1:0: Character Size
 *         • Bit 0 – UCPOL: Clock Polarity
 * */
#define UCSRC_URSEL   7
#define UCSRC_UMSEL   6
#define UCSRC_UPM1    5
#define UCSRC_UPM0    4
#define UCSRC_USBS    3
#define UCSRC_UCSZ1   2
#define UCSRC_UCSZ0   1
#define UCSRC_UCPOL   0

#define UBRRH 	(*((volatile uint8*)0x40))
#define UBRRL 	(*((volatile uint8*)0x29))
#define UDR 	(*((volatile uint8*)0x2C))

#define NO_PARITY                   1
#define EVEN_PARITY                 2
#define ODD_PARITY                  3

#define TRANSMITTER                 1
#define RECIEVER                    2
#define TRANSIVER                   3

#define ASYNCHROUNUS_NORMAL_SPEED        0
#define ASYNCHROUNUS_DOUBLE_SPEED        1
#define SYNCHROUNUS_MASTER_MODE          2

#define  TX_CHANGED_ON_RISING_RX_SAMPLED_ON_FALLING		0
#define  TX_CHANGED_ON_FALLING_RX_SAMPLED_ON_RISING		1

#endif /* MCAL_UART_V1_UART_PRV_H_ */
