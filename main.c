#include "main.h"

/* ����� 1:
		��� ������ � Storage Register ���������� �������� ������
���������� ����� ��������� �� ������� ���� MCU(����� �� ������� �����
STCLK(ST_CP) ���������� ������� �� �� mcu). ����� ����� ��� ����������� �
������������ �����.
	1. ������� �� spi ��� ��� ��������� ���������� �������.
	������� ���������� ����� ��� ������ � stoage register. 
	2. ������� �� spi ��� ��� ��� ����������� �� ��������
	������� ���������� ����� ��� ������ � stoage register.
*/

void Timer_Init()
{
	//TIMER0 init
	TCCR0 |= (1<<CS02)|(0<<CS00);
	TIMSK |= (1<<TOIE0);
}

// ��� ������������ �������
ISR(TIMER0_OVF_vect)
{
	DI_Update();
}

int main(void)
{
	DI_Init();
	Timer_Init();
	SPI_Init();
	
	uint32_t i = 0;

	sei();
	while (1) 
	{
		for(i = 9990; i < 100000; i++)
		{
			DI_Output(i, 2);
			_delay_ms(300);
		}
		i=0;
    }
}
