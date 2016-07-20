#ifndef FUZZYSETUP_H
#define FUZZYSETUP_H

#define MAXINMBNUM 0x07
#define MAXRULE  0x31

#define IN_MAXVALUE   1024
#define OUT_MAXVALUE  32767

#define _and(a, b) ((a)*(b))
#define _imp(a, b) ((a)*(b))

#include "fuzzyInt.h"

//PD-type Sugeno Fuzzy Module

FuzzyInput Ain1;
FuzzyInput Ain2;
FuzzyRule Arule;
Fuzzy Af;

void FuzzySetup(void) {
	inputInit(&Ain1,7,-1.0 * IN_MAXVALUE, 1.0 * IN_MAXVALUE);
	inputInit(&Ain2,7,-1.0 * IN_MAXVALUE, 1.0 * IN_MAXVALUE);
	fuzzyInit(&Af,&Ain1,&Ain2,&Arule);

	setTrimf(&Ain1,0,-1.0 * IN_MAXVALUE,-1.0 * IN_MAXVALUE,-1.0 * IN_MAXVALUE,-0.6 * IN_MAXVALUE);
	setTrimf(&Ain1,1,-1.0 * IN_MAXVALUE,-0.6 * IN_MAXVALUE,-0.6 * IN_MAXVALUE,-0.3 * IN_MAXVALUE);
	setTrimf(&Ain1,2,-0.6 * IN_MAXVALUE,-0.3 * IN_MAXVALUE,-0.3 * IN_MAXVALUE, 0.0 * IN_MAXVALUE);
	setTrimf(&Ain1,3,-0.3 * IN_MAXVALUE, 0.0 * IN_MAXVALUE, 0.0 * IN_MAXVALUE, 0.3 * IN_MAXVALUE);
	setTrimf(&Ain1,4, 0.0 * IN_MAXVALUE, 0.3 * IN_MAXVALUE, 0.3 * IN_MAXVALUE, 0.6 * IN_MAXVALUE);
	setTrimf(&Ain1,5, 0.3 * IN_MAXVALUE, 0.6 * IN_MAXVALUE, 0.6 * IN_MAXVALUE, 1.0 * IN_MAXVALUE);
	setTrimf(&Ain1,6, 0.6 * IN_MAXVALUE, 1.0 * IN_MAXVALUE, 1.0 * IN_MAXVALUE, 1.0 * IN_MAXVALUE);
	
	setTrimf(&Ain2,0,-1.0 * IN_MAXVALUE,-1.0 * IN_MAXVALUE,-1.0 * IN_MAXVALUE,-0.6 * IN_MAXVALUE);
	setTrimf(&Ain2,1,-1.0 * IN_MAXVALUE,-0.6 * IN_MAXVALUE,-0.6 * IN_MAXVALUE,-0.3 * IN_MAXVALUE);
	setTrimf(&Ain2,2,-0.6 * IN_MAXVALUE,-0.3 * IN_MAXVALUE,-0.3 * IN_MAXVALUE, 0.0 * IN_MAXVALUE);
	setTrimf(&Ain2,3,-0.3 * IN_MAXVALUE, 0.0 * IN_MAXVALUE, 0.0 * IN_MAXVALUE, 0.3 * IN_MAXVALUE);
	setTrimf(&Ain2,4, 0.0 * IN_MAXVALUE, 0.3 * IN_MAXVALUE, 0.3 * IN_MAXVALUE, 0.6 * IN_MAXVALUE);
	setTrimf(&Ain2,5, 0.3 * IN_MAXVALUE, 0.6 * IN_MAXVALUE, 0.6 * IN_MAXVALUE, 1.0 * IN_MAXVALUE);
	setTrimf(&Ain2,6, 0.6 * IN_MAXVALUE, 1.0 * IN_MAXVALUE, 1.0 * IN_MAXVALUE, 1.0 * IN_MAXVALUE);

	setRule(&Arule,0,6, 0.0 * OUT_MAXVALUE);
	setRule(&Arule,0,5,-0.3 * OUT_MAXVALUE);
	setRule(&Arule,0,4,-0.6 * OUT_MAXVALUE);
	setRule(&Arule,0,3,-1.0 * OUT_MAXVALUE);
	setRule(&Arule,0,2,-1.0 * OUT_MAXVALUE);
	setRule(&Arule,0,1,-1.0 * OUT_MAXVALUE);
	setRule(&Arule,0,0,-1.0 * OUT_MAXVALUE);

	setRule(&Arule,1,6, 0.3 * OUT_MAXVALUE);
	setRule(&Arule,1,5, 0.0 * OUT_MAXVALUE);
	setRule(&Arule,1,4,-0.3 * OUT_MAXVALUE);
	setRule(&Arule,1,3,-0.6 * OUT_MAXVALUE);
	setRule(&Arule,1,2,-0.6 * OUT_MAXVALUE);
	setRule(&Arule,1,1,-0.6 * OUT_MAXVALUE);
	setRule(&Arule,1,0,-1.0 * OUT_MAXVALUE);

	setRule(&Arule,2,6, 0.6 * OUT_MAXVALUE);
	setRule(&Arule,2,5, 0.3 * OUT_MAXVALUE);
	setRule(&Arule,2,4, 0.0 * OUT_MAXVALUE);
	setRule(&Arule,2,3,-0.3 * OUT_MAXVALUE);
	setRule(&Arule,2,2,-0.6 * OUT_MAXVALUE);
	setRule(&Arule,2,1,-0.6 * OUT_MAXVALUE);
	setRule(&Arule,2,0,-1.0 * OUT_MAXVALUE);

	setRule(&Arule,3,6, 1.0 * OUT_MAXVALUE);
	setRule(&Arule,3,5, 0.6 * OUT_MAXVALUE);
	setRule(&Arule,3,4, 0.3 * OUT_MAXVALUE);
	setRule(&Arule,3,3, 0.0 * OUT_MAXVALUE);
	setRule(&Arule,3,2,-0.3 * OUT_MAXVALUE);
	setRule(&Arule,3,1,-0.6 * OUT_MAXVALUE);
	setRule(&Arule,3,0,-1.0 * OUT_MAXVALUE);

	setRule(&Arule,4,6, 1.0 * OUT_MAXVALUE);
	setRule(&Arule,4,5, 0.6 * OUT_MAXVALUE);
	setRule(&Arule,4,4, 0.6 * OUT_MAXVALUE);
	setRule(&Arule,4,3, 0.3 * OUT_MAXVALUE);
	setRule(&Arule,4,2, 0.0 * OUT_MAXVALUE);
	setRule(&Arule,4,1,-0.3 * OUT_MAXVALUE);
	setRule(&Arule,4,0,-0.6 * OUT_MAXVALUE);

	setRule(&Arule,5,6, 1.0 * OUT_MAXVALUE);
	setRule(&Arule,5,5, 0.6 * OUT_MAXVALUE);
	setRule(&Arule,5,4, 0.6 * OUT_MAXVALUE);
	setRule(&Arule,5,3, 0.6 * OUT_MAXVALUE);
	setRule(&Arule,5,2, 0.3 * OUT_MAXVALUE);
	setRule(&Arule,5,1, 0.0 * OUT_MAXVALUE);
	setRule(&Arule,5,0,-0.3 * OUT_MAXVALUE);

	setRule(&Arule,6,6, 1.0 * OUT_MAXVALUE);
	setRule(&Arule,6,5, 1.0 * OUT_MAXVALUE);
	setRule(&Arule,6,4, 1.0 * OUT_MAXVALUE);
	setRule(&Arule,6,3, 1.0 * OUT_MAXVALUE);
	setRule(&Arule,6,2, 0.6 * OUT_MAXVALUE);
	setRule(&Arule,6,1, 0.3 * OUT_MAXVALUE);
	setRule(&Arule,6,0, 0.0 * OUT_MAXVALUE);

//	setFuzzifiType(&Af,0);
//	setAndType(&Af,1);

}


#endif

