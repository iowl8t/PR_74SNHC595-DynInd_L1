#include "dynIndSN74HC595_l1.h"

#define DOT_SEG	7

void ifDigit_0(void);
void ifDigit_1(void);
void ifDigit_2(void);
void ifDigit_3(void);
void digitGo(uint8_t digitCode, uint8_t segmentCode);

#ifdef COMMON_CATHODE
 uint8_t number[] = {0b00111111,	//0
						0b00000110,	//1
						0b01011011,	//2
						0b01001111,	//3
						0b01100110,	//4
						0b01101101,	//5
						0b01111101,	//6
						0b00000111,	//7
						0b01111111,	//8
						0b01101111};//9
#endif
#ifdef COMMON_ANODE
uint8_t number[] ={0b11000000, //0
					0b11111001, //1
					0b10100100, //2
					0b10110000, //3
					0b10011001, //4
					0b10010010, //5
					0b10000010, //6
					0b11111000, //7
					0b10000000, //8
					0b10010000};//9
#endif

uint8_t buff[AMOUNT_NUMBER];

void DI_Init()
{
	// Піни керування записом в Storage register
	DDRB |= (1<<PIN_FOR_DIGITS)|(1<<PIN_FOR_SEGMENT);
	PORTB &= ~((1<<PIN_FOR_DIGITS)|(1<<PIN_FOR_SEGMENT));
	// Обнуляємо буфер
	for(unsigned char i=0; i < AMOUNT_NUMBER; i++)
		buff[i] = 0;
}

void DI_Output(uint32_t value, uint8_t comm)
{
	// Закоментувати в залежності від кількості розрядів
	buff[0] = number[value%10];
	buff[1] = number[(value/10)%10];
	buff[2] = number[(value/100)%10];
	buff[3] = number[(value/1000)%10];
	// Ставимо кому
	if(comm < AMOUNT_NUMBER)
	{
		#ifdef COMMON_CATHODE
 		 buff[comm] |= (1<<DOT_SEG);  //128;
		#else
 		 buff[comm] &= ~(1<<DOT_SEG); //127
		#endif
	}
}

void DI_Update()
{	
	static uint8_t digit = 0;
	
	#ifdef COMMON_CATHODE 
		if (digit == 0)	digitGo(0b00001110, buff[0]);
		if (digit == 1)	digitGo(0b00001101, buff[1]);
		if (digit == 2)	digitGo(0b00001011, buff[2]);
		if (digit == 3)	digitGo(0b00000111, buff[3]);
	#elif COMMON_ANODE
		if (digit == 0)	digitGo(0b00000001, buff[0]);
		if (digit == 1)	digitGo(0b00000010, buff[1]);
		if (digit == 2)	digitGo(0b00000100, buff[2]);
		if (digit == 3)	digitGo(0b00001000, buff[3]);
	#endif
	
	digit++;
	if(digit == AMOUNT_NUMBER)	digit = 0;
}

/* Запис кода сегментів і вибору розряду в зсувний регістр і вивід на інд. */
void digitGo(uint8_t digitCode, uint8_t segmentCode)
{
		/* Вмикаємо розряд */
		// Заносимо в зсувний регістр дані
		SPI_SendByte(digitCode);
		// Фронт для запису в storage register, який керує вибором розряду
		PORTB |= (1<<PIN_FOR_DIGITS);
		PORTB &= ~(1<<PIN_FOR_DIGITS);
		
		/* Подаємо код на сегменти */
		// Заносимо в зсувний регістр дані
		SPI_SendByte(segmentCode);
		// Фронт для запису в storage register, який керує відображуваним значенням		
		PORTB |= (1<<PIN_FOR_SEGMENT);
		PORTB &= ~(1<<PIN_FOR_SEGMENT);
}
