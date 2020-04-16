#include "stm32f10x.h"

void delay(int ms) {
	long i;
	for (i = 0; i < 10000 * ms; i++) {}
}

int main(void) {
char valik[] = {'.', '.', '.', '_', ' ', '.', '_', ' ', '.', '_', '.', '.', ' ', '.', '.', ' ', '_', '.', '_'};
int length = sizeof(valik) / sizeof(char);
int *GPIOx_CRL = (int*) (0x40010C00);
int *GPIOx_CRH = (int*)(0x40010C04);
int *GPIOx_ODR = (int*)(0x40010C0C);

int *apb2enr = (int*) (0x40021018);
*apb2enr |= 0x00018;
*GPIOx_CRL = 0x00000500;
*GPIOx_CRH = 0x00000008;

int i;

for(;;) {
		char element = valik[i % length];
		if(element == '.') {
			*GPIOx_ODR=0x00000020;
			delay(300);
		} else if(element == '_') {
			*GPIOx_ODR=0x00000020;
			delay(500);
		} else if(element == ' ') {
			*GPIOx_ODR=0x0000000;
			delay(800);
		}
		i++;
		if(i % length == length - 1) {
			delay(3000);
			i = 0;
		};
	}
}
