/*
 * I2C_prv.h
 *
 *  Created on: Sep 28, 2023
 *      Author: Emii
 */

#ifndef MCAL_I2C_V1_I2C_PRV_H_
#define MCAL_I2C_V1_I2C_PRV_H_


#define TWI_STATUS_VALUE              (TWSR&0xF8)

#define TWI_START_CONDITION_ACK       0x08
#define TWI_REP_START_CONDITION_ACK   0x10
#define TWI_SLAVE_ADDRESS_WRITE_ACK   0x18
#define TWI_SLAVE_ADDRESS_READ_ACK    0x40
#define TWI_MASTER_DATA_TRANSMIT_ACK  0x28
#define TWI_MASTER_DATA_RECIEVE_ACK   0x50


                         /* TWI REGISTERS */

// TWI Bit Rate Register
#define TWBR         (*(volatile uint8*)0x20)

// TWI Control Register
#define TWCR         (*(volatile uint8*)0x56)
#define TWIE         0
#define TWEN         2
#define TWWC         3
#define TWSTO        4
#define TWSTA        5
#define TWEA         6
#define TWINT        7


// TWI Status Register
#define TWSR         (*(volatile uint8*)0x21)
#define TWPS0        0
#define TWPS1        1

// TWI Data Register
#define TWDR         (*(volatile uint8*)0x23)

// TWI (Slave) Address Register
#define TWAR         (*(volatile uint8*)0x22)
#define TWGCE        0


#endif /* MCAL_I2C_V1_I2C_PRV_H_ */
