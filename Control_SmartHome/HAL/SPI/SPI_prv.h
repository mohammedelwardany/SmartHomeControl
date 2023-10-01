/*
 * SPI_prv.h
 *
 *  Created on: Sep 28, 2023
 *      Author: Emii
 */

#ifndef MCAL_SPI_V1_SPI_PRV_H_
#define MCAL_SPI_V1_SPI_PRV_H_

/* SPCR : SPI Control Register – SPCR
 * Bit  7   6   5    4    3     2    1   0
      SPIE SPE DORD MSTR CPOL CPHA SPR1 SPR0
 * */

#define ENABLED                                   0b10000000
#define DISABLED                                  0b00000000

#define LSB_TRANSMITTED_FIRST                     0b00100000
#define MSB_TRANSMITTED_FIRST                     0b00000000

/*
 * Table 59. CPOL and CPHA Functionality
                                           SPI Mode
          CPOL = 0, CPHA = 0                  0
          CPOL = 0, CPHA = 1                  1
          CPOL = 1, CPHA = 0                  2
          CPOL = 1, CPHA = 1                  3
 *
 * */

#define MODE_0                                    0b00000000
#define MODE_1                                    0b00000100
#define MODE_2                                    0b00001000
#define MODE_3                                    0b00001100

#define NORMAL_SPEED_FOSC_OVER_4            	  0
#define NORMAL_SPEED_FOSC_OVER_16                 1
#define NORMAL_SPEED_FOSC_OVER_64                 2
#define NORMAL_SPEED_FOSC_OVER_128                3
#define DOUBLE_SPEED_FOSC_OVER_2                  4
#define DOUBLE_SPEED_FOSC_OVER_8                  5
#define DOUBLE_SPEED_FOSC_OVER_32                 6
#define DOUBLE_SPEED_FOSC_OVER_64                 7

/*
 * SPI2X SPR1 SPR0 SCK Frequency
     0    0     0     fosc/4        | NORMAL_SPEED
     0    0     1     fosc/16       | NORMAL_SPEED
     0    1     0     fosc/64       | NORMAL_SPEED
     0    1     1     fosc/128      | NORMAL_SPEED
     1    0     0     fosc/2        | DOUBLE_SPEED
     1    0     1     fosc/8        | DOUBLE_SPEED
     1    1     0     fosc/32       | DOUBLE_SPEED
     1    1     1     fosc/64       | DOUBLE_SPEED
 * */

//IN SPCR
#define SPCR_NORMAL_SPEED_FOSC_OVER_4              0b00000000
#define SPCR_NORMAL_SPEED_FOSC_OVER_16             0b00000001
#define SPCR_NORMAL_SPEED_FOSC_OVER_64             0b00000010
#define SPCR_NORMAL_SPEED_FOSC_OVER_128            0b00000011
#define SPCR_DOUBLE_SPEED_FOSC_OVER_2              0b00000000
#define SPCR_DOUBLE_SPEED_FOSC_OVER_8              0b00000001
#define SPCR_DOUBLE_SPEED_FOSC_OVER_32             0b00000010
#define SPCR_DOUBLE_SPEED_FOSC_OVER_64             0b00000011

/*    SPSR : SPI Status Register – SPSR
 * Bit  7   6   5 4 3 2 1   0
      SPIF WCOL – – – – – SPI2X */
//IN SPSR
#define SPSR_NORMAL_SPEED_FOSC_OVER_4              0b00000000
#define SPSR_NORMAL_SPEED_FOSC_OVER_16             0b00000000
#define SPSR_NORMAL_SPEED_FOSC_OVER_64             0b00000000
#define SPSR_NORMAL_SPEED_FOSC_OVER_128            0b00000000
#define SPSR_DOUBLE_SPEED_FOSC_OVER_2              0b00000001
#define SPSR_DOUBLE_SPEED_FOSC_OVER_8              0b00000001
#define SPSR_DOUBLE_SPEED_FOSC_OVER_32             0b00000001
#define SPSR_DOUBLE_SPEED_FOSC_OVER_64             0b00000001

#if OSCILLATOR_FREQUENCY == NORMAL_SPEED_FOSC_OVER_4
//In SPCR
#define OSCILLATOR_FREQUENCY_SPCR             SPCR_NORMAL_SPEED_FOSC_OVER_4
//In SPSR
#define OSCILLATOR_FREQUENCY_SPSR             SPSR_NORMAL_SPEED_FOSC_OVER_4

#elif OSCILLATOR_FREQUENCY == NORMAL_SPEED_FOSC_OVER_16
//In SPCR
#define OSCILLATOR_FREQUENCY_SPCR             SPCR_NORMAL_SPEED_FOSC_OVER_16
//In SPSR
#define OSCILLATOR_FREQUENCY_SPSR             SPSR_NORMAL_SPEED_FOSC_OVER_16

#elif OSCILLATOR_FREQUENCY == NORMAL_SPEED_FOSC_OVER_64
//In SPCR
#define OSCILLATOR_FREQUENCY_SPCR             SPCR_NORMAL_SPEED_FOSC_OVER_64
//In SPSR
#define OSCILLATOR_FREQUENCY_SPSR             SPSR_NORMAL_SPEED_FOSC_OVER_64

#elif OSCILLATOR_FREQUENCY == NORMAL_SPEED_FOSC_OVER_128
//In SPCR
#define OSCILLATOR_FREQUENCY_SPCR             SPCR_NORMAL_SPEED_FOSC_OVER_128
//In SPSR
#define OSCILLATOR_FREQUENCY_SPSR             SPSR_NORMAL_SPEED_FOSC_OVER_128

#elif OSCILLATOR_FREQUENCY == DOUBLE_SPEED_FOSC_OVER_2
//In SPCR
#define OSCILLATOR_FREQUENCY_SPCR             SPCR_DOUBLE_SPEED_FOSC_OVER_2
//In SPSR
#define OSCILLATOR_FREQUENCY_SPSR             SPSR_DOUBLE_SPEED_FOSC_OVER_2

#elif OSCILLATOR_FREQUENCY == DOUBLE_SPEED_FOSC_OVER_8
//In SPCR
#define OSCILLATOR_FREQUENCY_SPCR             SPCR_DOUBLE_SPEED_FOSC_OVER_8
//In SPSR
#define OSCILLATOR_FREQUENCY_SPSR             SPSR_DOUBLE_SPEED_FOSC_OVER_8

#elif OSCILLATOR_FREQUENCY == DOUBLE_SPEED_FOSC_OVER_32
//In SPCR
#define OSCILLATOR_FREQUENCY_SPCR             SPCR_DOUBLE_SPEED_FOSC_OVER_32
//In SPSR
#define OSCILLATOR_FREQUENCY_SPSR             SPSR_DOUBLE_SPEED_FOSC_OVER_32

#elif OSCILLATOR_FREQUENCY == DOUBLE_SPEED_FOSC_OVER_64
//In SPCR
#define OSCILLATOR_FREQUENCY_SPCR             SPCR_DOUBLE_SPEED_FOSC_OVER_64
//In SPSR
#define OSCILLATOR_FREQUENCY_SPSR             SPSR_DOUBLE_SPEED_FOSC_OVER_64

#endif

#define SPCR       (*((volatile uint8*)0X2D))
/* SPCR : SPI Control Register – SPCR
 * Bit  7   6   5    4    3     2    1   0
      SPIE SPE DORD MSTR CPOL CPHA SPR1 SPR0
 * */
typedef enum {
	SPR0,
	SPR1,
	CPHA,
	CPOL,
	MSTR,
	DORD,
	SPE,
	SPIE
}SPCR_BITS;

#define SPSR       (*((volatile uint8*)0X2E))
/*    SPSR : SPI Status Register – SPSR
 * Bit  7   6   5 4 3 2 1   0
      SPIF WCOL – – – – – SPI2X */

typedef enum {
	SPI2X,
	WCOL = 6,
	SPIF = 7
}SPSR_BITS;

#define SPDR       (*((volatile uint8*)0X2F))
/*    SPDR : SPI Data Register
 * Bit 7  6 5 4 3 2 1  0
      MSB             LSB
 * */
typedef enum {
	LSB,
	MSB = 7
}SPDR_BITS;



#endif /* MCAL_SPI_V1_SPI_PRV_H_ */
