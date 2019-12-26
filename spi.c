#include "spi.h"

// Serial Peripheral Interface Bus(SPI) Ч посл≥довна шина.

void SPI_Init(void)
{
	DDRB	|=  /*(1<<PORTB2)|*/(1<<PORTB3)|(1<<PORTB5); //SS(1<<PORTB2) - MOSI(1<<PORTB3) - SCK(1<<PORTB5)
	PORTB	&= ~(/*(1<<PORTB2)|*/(1<<PORTB3)|(1<<PORTB5));
	// якщо використовуЇтьс€ то ≥н≥ц≥ал≥зувати
	/*DDRB	&= ~(1<<PORTB4); //MISO
	PORTB	|= (1<<PORTB4); //MISO*/
	SPCR |= (1<<SPE)|(1<<MSTR);
}

void SPI_SendByte(uint8_t byte)
{
	SPDR = byte;
	while (!(SPSR&(1<<SPIF)));
}



/************************
MOSI (master output slave input) Ч н≥жка виходу master ≥ входу slave.
MISO (master input slave output) Ч н≥жка входу master ≥ виходу slave.
SCK (serial clock) Ч н≥жка синхрон≥зац≥њ. ѕо н≥й передаютьс€ синхро≥мпульси певноњ частоти, до вс≥х пистроњв, €к≥ беруть участь в обм≥н≥.
SS (chip select) Ч н≥жка вибору пристрою. якщо у slave на н≥й буде низький р≥вень, в≥н буде в≥дкликатис€ ≥ обм≥нюватис€ даними по spi.

************************
Registers:
SPDR (SPI Data Register) Ч рег≥стр даних. ¬ нього заносимо дан≥ дл€ передач≥ чи зчитуЇмо отриман≥.

SPCR (SPI Control Register) Ч керуючий рег≥стр:
	SPIE (SPI Interrupt Enable) Ч б≥т дозволу переривань.
	SPE (SPI Enable) Ч б≥т дл€ ув≥мкненн€ шини SPI.
	DORD (Data Order) Ч б≥т встановленн€ пор€дку надсиланн€ байту. 1 - першим над≥шлетьс€ lsb, 0 Ч msb.
	MSTR (Master/Slave Select) Ч б≥т встановленн€ пристрою майстром чи слейвом. 0 - master, 1 - slave.
	CPOL (Clock Polarity) Ч пол€рн≥сть синхрон≥зац≥њ. ¬изначаЇ стан шини в режим≥ оч≥куванн€. 0 - низький р≥вень на шин≥, 1 - високий
	CPHA (Clock Phase) Ч б≥т в≥дпов≥даЇ за фазу тактуванн€, тобто по €кому фронту буде зд≥йснюватис€ передача б≥та. 0 - first edge, 1 - last edge.
	«алежно в≥д значень CPOL ≥ CPHA Ї 4 режими передач≥.
	SPR1, SPR0 (SPI Clock Rate Select) Ч б≥ти встановленн€ д≥льника частоти синхрон≥зац≥њ, визначають частоту разом ≥з SPI2X.

SPSR (SPI Status Register) Ч статусний рег≥стр:
	SPI2X (Double SPI Speed Bit) Ч б≥т подвоЇнн€ швидкост≥.
	SPIF (SPI Interrupt Flag) Ч прапорець перериванн€. ¬становлюЇтьс€ €к т≥льки ми передамо/приймемо ц≥лий байт.
	WCOL (Write COLlision Flag) Ч прапорець кол≥з≥й(кнфл≥кту). ¬становлЇтсь€ при спроб≥ запису в SPDR прот€гом передач≥.
 */

