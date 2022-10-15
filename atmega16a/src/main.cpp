#include <avr/io.h> // contains definitions for DDRB, PORTB
#include <avr/interrupt.h>
#include <util/delay.h> // contains the function _delay_ms()

// char hello[4] = {'H', 'E', 'L', 'P'};
// char righthere[9] = {'R', 'I', 'G', 'H', 'T', 'H', 'E', 'R', 'E'};
// char run[3] = {'R', 'U', 'N'};
// char happyhalloween[14] = {'H', 'A', 'P', 'P', 'Y', 'H', 'A', 'L', 'L', 'O', 'W', 'E', 'E', 'N'};

int pwmtable[16] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};

void allLightsOn(){
	PORTA = 0b11111111;
	PORTB = 0b11111111;
	PORTC = 0b11111111;
	PORTD = 0b11111111;
}

void allLightsOff(){
	PORTA = 0b00000000;
	PORTB = 0b00000000;
	PORTC = 0b00000000;
	PORTD = 0b00000000;
}

void my_delay (int milliseconds)
{
	for (; milliseconds > 0; milliseconds--)
	_delay_ms (1);
}

void choose_port(int pin, char port_letter, char on_off){
	if (on_off == 'o'){
		if (port_letter == 'A'){PORTA = pin;}
		else if (port_letter == 'B'){PORTB = pin;}
		else if (port_letter == 'C'){PORTC = pin;}
		else if (port_letter == 'D'){PORTD = pin;}
		} 
	else if(on_off == 'f'){
		if (port_letter == 'A'){PORTA = 0x00;}
		else if (port_letter == 'B'){PORTB = 0x00;}
		else if (port_letter == 'C'){PORTC = 0x00;}
		else if (port_letter == 'D'){PORTD = 0x00;}
	}
}

void smooth_blink(char letter, char port_letter, int pin){
	
	for (int i = 0; i < 16; i++)
	{
		int highDelay = pwmtable[i];
		int lowDelay = pwmtable[16 - i];
		choose_port(pin, port_letter, 'f');
		my_delay(lowDelay);
		choose_port(pin, port_letter, 'o');
		my_delay (highDelay);
	}
	
	for (int i = 0; i < 16; i++)
	{
		int highDelay = pwmtable[i];
		int lowDelay = pwmtable[16 - i];
		choose_port(pin, port_letter, 'f');
		my_delay(highDelay);
		choose_port(pin, port_letter, 'o');
		my_delay (lowDelay);
	}
}

int main()
{
	DDRA = 0xFF;
	DDRB = 0xFF;
	DDRC = 0xFF;
    DDRD = 0xFF;
	
	smooth_blink('A', 'B', 0b1);
	smooth_blink('D', 'B', 0b1000);
	smooth_blink('E', 'B', 0b10000);
	
	allLightsOn();
	
	while(1){}
	
	return 0;
}