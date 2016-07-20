// $ LANG=C gcc -Wall -o test *.c -lm

#include <stdio.h>
#include <stdlib.h>
#include "fuzzysetupIntC.h"


Foutput_t a;

int main() {
	int i;

	FuzzySetup();
/*
	degOfFire(&Af, 256, -512);
//	degOfFire(&Af, 0.25, -0.5);
	a = deFuzzication(&Af);
//	printf("%3.3f\r\n",a);
	printf("%d\n", a);
*/
	for(i=-200; i<200; i++){
		degOfFire(&Af, i, 0);
		a = deFuzzication(&Af);
		printf("%d\t%d\n", i, a);
	}

	return 0;
}

