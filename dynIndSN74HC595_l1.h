#ifndef dynIndSN74HC595_l1_H_
#define dynIndSN74HC595_l1_H_
/* На індикаторі в Proteus навпаки: 4-й - це нульовий розряд */

#include "spi.h"

#include <avr/io.h>
#include <inttypes.h>

//#define COMMON_CATHODE	1
#define COMMON_ANODE	1

#define AMOUNT_NUMBER 4

/*
	Пін формування фронту для запису даних в SN74HC595 
	з Shift reg. в Storage reg. для керування сегментами
*/
#define PIN_FOR_SEGMENT	PB2		

/*
	Пін формування фронту для запису даних в SN74HC595 з
	Shift reg. в Storage reg. для керування перемиканням розрядів
*/
#define PIN_FOR_DIGITS	PB1

// Очистка буфера індикатора
void DI_Init();

/*  value - число для перетворення
	comma - позиція коми на індикаторі(якщо не потрібно ставимо більше за AMOUNT_NUM)
	Перетворює 16 розрядне беззнакове в bcd і записує в буфер	*/
void DI_Output(uint32_t value, uint8_t comm);	

/*  Виводить з буфера на індикатор
	Можна викликати в перериванні таймера	*/
void DI_Update();



#endif /* dynIndSN74HC595_l1_H_ */

/*unsigned char number[] =
{
	(1<<SEG_A)|(1<<SEG_B)|(1<<SEG_C)|(1<<SEG_D)|(1<<SEG_E)|(1<<SEG_F)|(0<<SEG_G), //0
	(0<<SEG_A)|(1<<SEG_B)|(1<<SEG_C)|(0<<SEG_D)|(0<<SEG_E)|(0<<SEG_F)|(0<<SEG_G), //1
	(1<<SEG_A)|(1<<SEG_B)|(0<<SEG_C)|(1<<SEG_D)|(1<<SEG_E)|(0<<SEG_F)|(1<<SEG_G), //2
	(1<<SEG_A)|(1<<SEG_B)|(1<<SEG_C)|(1<<SEG_D)|(0<<SEG_E)|(0<<SEG_F)|(1<<SEG_G), //3
	(0<<SEG_A)|(1<<SEG_B)|(1<<SEG_C)|(0<<SEG_D)|(0<<SEG_E)|(1<<SEG_F)|(1<<SEG_G), //4
	(1<<SEG_A)|(0<<SEG_B)|(1<<SEG_C)|(1<<SEG_D)|(0<<SEG_E)|(1<<SEG_F)|(1<<SEG_G), //5
	(1<<SEG_A)|(0<<SEG_B)|(1<<SEG_C)|(1<<SEG_D)|(1<<SEG_E)|(1<<SEG_F)|(1<<SEG_G), //6
	(1<<SEG_A)|(1<<SEG_B)|(1<<SEG_C)|(0<<SEG_D)|(0<<SEG_E)|(0<<SEG_F)|(0<<SEG_G), //7
	(1<<SEG_A)|(1<<SEG_B)|(1<<SEG_C)|(1<<SEG_D)|(1<<SEG_E)|(1<<SEG_F)|(1<<SEG_G), //8
	(1<<SEG_A)|(1<<SEG_B)|(1<<SEG_C)|(1<<SEG_D)|(0<<SEG_E)|(1<<SEG_F)|(1<<SEG_G)  //9
};
//для індикатора зі спільним анодом
unsigned char number[] =
{
	(0<<SEG_A)|(0<<SEG_B)|(0<<SEG_C)|(0<<SEG_D)|(0<<SEG_E)|(0<<SEG_F)|(1<<SEG_G), //0
	(1<<SEG_A)|(0<<SEG_B)|(0<<SEG_C)|(1<<SEG_D)|(1<<SEG_E)|(1<<SEG_F)|(1<<SEG_G), //1
	(0<<SEG_A)|(0<<SEG_B)|(1<<SEG_C)|(0<<SEG_D)|(0<<SEG_E)|(1<<SEG_F)|(0<<SEG_G), //2
	(0<<SEG_A)|(0<<SEG_B)|(0<<SEG_C)|(0<<SEG_D)|(1<<SEG_E)|(1<<SEG_F)|(0<<SEG_G), //3
	(1<<SEG_A)|(0<<SEG_B)|(0<<SEG_C)|(1<<SEG_D)|(1<<SEG_E)|(0<<SEG_F)|(0<<SEG_G), //4
	(0<<SEG_A)|(1<<SEG_B)|(0<<SEG_C)|(0<<SEG_D)|(1<<SEG_E)|(0<<SEG_F)|(0<<SEG_G), //5
	(0<<SEG_A)|(1<<SEG_B)|(0<<SEG_C)|(0<<SEG_D)|(0<<SEG_E)|(0<<SEG_F)|(0<<SEG_G), //6
	(0<<SEG_A)|(0<<SEG_B)|(0<<SEG_C)|(1<<SEG_D)|(1<<SEG_E)|(1<<SEG_F)|(1<<SEG_G), //7
	(0<<SEG_A)|(0<<SEG_B)|(0<<SEG_C)|(0<<SEG_D)|(0<<SEG_E)|(0<<SEG_F)|(0<<SEG_G), //8
	(0<<SEG_A)|(0<<SEG_B)|(0<<SEG_C)|(0<<SEG_D)|(1<<SEG_E)|(0<<SEG_F)|(0<<SEG_G)  //9
};*/