#include "spi.h"

// Serial Peripheral Interface Bus(SPI) � ��������� ����.

void SPI_Init(void)
{
	DDRB	|=  /*(1<<PORTB2)|*/(1<<PORTB3)|(1<<PORTB5); //SS(1<<PORTB2) - MOSI(1<<PORTB3) - SCK(1<<PORTB5)
	PORTB	&= ~(/*(1<<PORTB2)|*/(1<<PORTB3)|(1<<PORTB5));
	// ���� ��������������� �� ������������
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
MOSI (master output slave input) � ���� ������ master � ����� slave.
MISO (master input slave output) � ���� ����� master � ������ slave.
SCK (serial clock) � ���� ������������. �� �� ����������� ������������� ����� �������, �� ��� �������, �� ������ ������ � ����.
SS (chip select) � ���� ������ ��������. ���� � slave �� �� ���� ������� �����, �� ���� ����������� � ����������� ������ �� spi.

************************
Registers:
SPDR (SPI Data Register) � ������ �����. � ����� �������� ��� ��� �������� �� ������� �������.

SPCR (SPI Control Register) � �������� ������:
	SPIE (SPI Interrupt Enable) � �� ������� ����������.
	SPE (SPI Enable) � �� ��� ��������� ���� SPI.
	DORD (Data Order) � �� ������������ ������� ���������� �����. 1 - ������ ���������� lsb, 0 � msb.
	MSTR (Master/Slave Select) � �� ������������ �������� �������� �� �������. 0 - master, 1 - slave.
	CPOL (Clock Polarity) � ��������� ������������. ������� ���� ���� � ����� ����������. 0 - ������� ����� �� ���, 1 - �������
	CPHA (Clock Phase) � �� ������� �� ���� ����������, ����� �� ����� ������ ���� ������������ �������� ���. 0 - first edge, 1 - last edge.
	������� �� ������� CPOL � CPHA � 4 ������ ��������.
	SPR1, SPR0 (SPI Clock Rate Select) � ��� ������������ ������� ������� ������������, ���������� ������� ����� �� SPI2X.

SPSR (SPI Status Register) � ��������� ������:
	SPI2X (Double SPI Speed Bit) � �� �������� ��������.
	SPIF (SPI Interrupt Flag) � ��������� �����������. �������������� �� ����� �� ��������/�������� ����� ����.
	WCOL (Write COLlision Flag) � ��������� �����(�������). ������������ ��� ����� ������ � SPDR �������� ��������.
 */

