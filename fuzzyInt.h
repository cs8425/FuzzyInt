#ifndef __FUZZY_H
#define __FUZZY_H

#include <stdint.h>

#include <stdio.h>
//#define _debug 1

#define Frule_t   int32_t
#define Finput_t  int16_t
#define Foutput_t int64_t
#define Fmbf_t    int32_t
#define Ftype_t   int32_t

/*
#define Frule_t   float
#define Finput_t  float
#define Fmbf_t    float
#define Foutput_t float
#define Ftype_t   float
*/
#define MAXINMBNUM 0x07 
#define MAXRULE  0x31

#define MAXVALUE     32767

#define min(a, b) (((b) > (a)) ? (a) : (b))

typedef struct {
	uint8_t ID;
//	uint8_t Type;
	Fmbf_t left;
	Fmbf_t middleL;
	Fmbf_t middleR;
	Fmbf_t right;
	Fmbf_t slopeL;
	Fmbf_t slopeR;
} MembershipFunction;

typedef struct {
	MembershipFunction _inMf[MAXINMBNUM];
	uint8_t _maxInMfNum;
	Finput_t _maxInRangeL;
	Finput_t _maxInRangeR;
} FuzzyInput;

void inputInit(FuzzyInput* fi, uint8_t inMfNum, Finput_t inRangeL, Finput_t inRangeR) {
	fi->_maxInMfNum = inMfNum;
	fi->_maxInRangeL = inRangeL; 
	fi->_maxInRangeR = inRangeR;
}

int8_t setTrimf(FuzzyInput* fi, uint8_t mfID, Finput_t left, Finput_t middleLeft, Finput_t middleRight, Finput_t right) {
	int8_t state = 0;
	Finput_t tmp = 0;
	if(mfID < fi->_maxInMfNum) {
		fi->_inMf[mfID].ID = mfID;
//		fi->_inMf[mfID].Type = 0;
		fi->_inMf[mfID].left = left;
		fi->_inMf[mfID].middleL = middleLeft;
		fi->_inMf[mfID].middleR = middleRight;
		fi->_inMf[mfID].right = right;
//		fi->_inMf[mfID].slopeL = (middleLeft - left) / MAXVALUE;
//		fi->_inMf[mfID].slopeR = (middleRight - right) / MAXVALUE;

		tmp = (middleLeft - left);
		fi->_inMf[mfID].slopeL = (tmp == 0) ? 0 : MAXVALUE / tmp;

		tmp = (middleRight - right);
		fi->_inMf[mfID].slopeR = (tmp == 0) ? 0 : MAXVALUE / tmp;

		state = 0;
	} else {
		state = -1;
	}

	return state;
}

typedef struct {
	Frule_t _ruleTable[MAXINMBNUM][MAXINMBNUM];
} FuzzyRule;

int8_t setRule(FuzzyRule* fr, uint8_t rule1, uint8_t rule2, Frule_t output) {
	int8_t state = 0;

	if(rule1<MAXINMBNUM && rule2<MAXINMBNUM) {
		fr->_ruleTable[rule1][rule2] = output;
		state = 0;
	} else {
		state = -1;
	}	

	return state;
}
       
Frule_t getRule(FuzzyRule* fr, uint8_t in1, uint8_t in2) {
	return fr->_ruleTable[in1][in2];
}

typedef struct {

	FuzzyInput *_input1; 
	FuzzyInput *_input2;
	FuzzyRule *_rule1; 
	Ftype_t _in1Degree[MAXINMBNUM];
	Ftype_t _in2Degree[MAXINMBNUM];
	uint8_t _in1Active[MAXINMBNUM];
	uint8_t _in1ActNum;
	uint8_t _in2Active[MAXINMBNUM];
	uint8_t _in2ActNum;
//	uint8_t _fuzzifiType;
//	uint8_t _andType;
//	uint8_t _impType;
	Finput_t _inMaxR[2];
	Finput_t _inMaxL[2];

} Fuzzy;

void fuzzyInit(Fuzzy *fy,FuzzyInput *in1, FuzzyInput *in2, FuzzyRule *rule) {
	fy->_input1 = in1;
	fy->_input2 = in2;
	fy->_rule1 = rule; 
	fy->_inMaxR[0] =  fy->_input1->_maxInRangeR;
	fy->_inMaxL[0] =  fy->_input1->_maxInRangeL;
	fy->_inMaxR[1] =  fy->_input2->_maxInRangeR;
	fy->_inMaxL[1] =  fy->_input2->_maxInRangeL;
}
/*
int8_t setFuzzifiType(Fuzzy *fy, uint8_t fuzziType) {
	int8_t state = 0;

	switch(fuzziType) {
		case 0:
			fy->_fuzzifiType = 0;
			state = 0;
			break;
		case 1:
			fy->_fuzzifiType = 1;
			state = 0;
			break;
		default:
			state = -1;
			break;
	}   
	return state;
}

int8_t setAndType(Fuzzy *fy, uint8_t andType) {
	int8_t state = 0;

	switch(andType) {
		case 0:
			fy->_andType = 0;
			state = 0;
			break;
		case 1:
			fy->_andType = 1;
			state = 0;
			break;
		default:
			state = -1;
			break;
	}   
	return state;
}

int8_t setImpType(Fuzzy *fy,uint8_t impType) {
	int8_t state = 0;

	switch(impType) {
		case 0:
			fy->_impType = 0;
			state = 0;
			break;
		case 1:
			fy->_impType = 1;
			state = 0;
			break;
		default:
			state = -1;
			break;
	}   
	return state;
}
*/
int8_t degOfFire(Fuzzy *fy, Finput_t sysin1, Finput_t sysin2) {
	Ftype_t d1=0.0,v1=0.0,v2=0.0;
	uint8_t index=0,i=0,j=0;
	int8_t result=0;
	
	if( sysin1 >= fy->_inMaxR[0]) sysin1 = fy->_inMaxR[0];
	if( sysin1 <= fy->_inMaxL[0]) sysin1 = fy->_inMaxL[0];

	if( sysin2 >= fy->_inMaxR[1]) sysin2 = fy->_inMaxR[1];
	if( sysin2 <= fy->_inMaxL[1]) sysin2 = fy->_inMaxL[1];

    
	for(index=0; index<MAXINMBNUM; index++) {

		if( sysin1 < fy->_input1->_inMf[index].left ) {
			v1 = 0;
		} else if( sysin1 < fy->_input1->_inMf[index].middleL ) {
			d1 = sysin1 - fy->_input1->_inMf[index].left;
//			v1 = d1 / fy->_input1->_inMf[index].slopeL;
//			v1 = (d1 == 0) ? 0 : fy->_input1->_inMf[index].slopeL * d1;
			v1 = fy->_input1->_inMf[index].slopeL * d1;
		} else if( sysin1 <= fy->_input1->_inMf[index].middleR ) {
			v1 = MAXVALUE;
		} else if( sysin1 < fy->_input1->_inMf[index].right ) {
			d1 = sysin1 - fy->_input1->_inMf[index].right;
//			v1 = d1 / fy->_input1->_inMf[index].slopeR;
//			v1 = (d1 == 0) ? 0 : fy->_input1->_inMf[index].slopeR * d1;
			v1 = fy->_input1->_inMf[index].slopeR * d1;
		} else {
			v1 = 0;
		}


		if( sysin2 < fy->_input2->_inMf[index].left ) {
			v2 = 0;
		} else if( sysin2 < fy->_input2->_inMf[index].middleL ) {
			d1 = sysin2 - fy->_input2->_inMf[index].left;
//			v2 = d1 / fy->_input2->_inMf[index].slopeL;
//			v2 = (d1 == 0) ? 0 : fy->_input2->_inMf[index].slopeL * d1;
			v2 = fy->_input2->_inMf[index].slopeL * d1;
		} else if( sysin2 <= fy->_input2->_inMf[index].middleR ) {
			v2 = MAXVALUE;
		} else if( sysin2 < fy->_input2->_inMf[index].right ) {
			d1 = sysin2 - fy->_input2->_inMf[index].right;
//			v2 = d1 / fy->_input2->_inMf[index].slopeR;
//			v2 = (d1 == 0) ? 0 : fy->_input2->_inMf[index].slopeR * d1;
			v2 = fy->_input2->_inMf[index].slopeR * d1;
		} else {
			v2 = 0;
		}
        
		fy->_in1Degree[index] = v1;
		if(v1 != 0) {
			fy->_in1Active[i] = index;
			#ifdef _debug
			printf("Input0 MF%d Degree:%d\r\n",index,v1);
//			printf("Input0 MF%d Degree:%E\r\n",index,v1);
			#endif
			i++;
			fy->_in1ActNum = i;
		}


		fy->_in2Degree[index] = v2;
		if(v2 != 0) {
			fy->_in2Active[j] = index;
			#ifdef _debug
			printf("Input1 MF%d Degree:%d\r\n",index,v2);
//			printf("Input1 MF%d Degree:%E\r\n",index,v2);
			#endif
			j++;
			fy->_in2ActNum = j;
		}
	}      
	return result; 
}
Foutput_t deFuzzication(Fuzzy *fy) {
	uint8_t j,i,ri1,ri2;
	Foutput_t valuei=0.0,num=0.0,den=0.0,a1=0.0,result=0.0;
	Foutput_t valueo=0.0;
/*
	switch(fy->_andType) {
		case 0:
			for(j=0; j<fy->_in2ActNum; j++) {
				for(i=0; i<fy->_in1ActNum; i++) {
					ri1 = fy->_in1Active[i];
					ri2 = fy->_in2Active[j];
					valuei = min(fy->_in1Degree[ri1],fy->_in2Degree[ri2]);

					valueo = getRule(fy->_rule1,ri1,ri2);

					switch(fy->_impType) {
						case 0:
							a1 = min((double)valuei, (double)valueo);
							break;
						case 1:
							a1 = (double)valuei * (double)valueo;
							break;
						default:
							break;
					}
					num = num + a1;
					den = den + valuei;
				}   
			}
			result = num / den;
			break;
		case 1:
*/
			for(j=0; j<fy->_in2ActNum; j++) {
				for(i=0; i<fy->_in1ActNum; i++) {
					ri1 = fy->_in1Active[i];
					ri2 = fy->_in2Active[j];
					valuei = fy->_in1Degree[ri1] * fy->_in2Degree[ri2];

					valueo = getRule(fy->_rule1,ri1,ri2);

					a1 = valuei * valueo;
/*
					switch(fy->_impType) {
						case 0:
							a1 = min((double)valuei, (double)valueo);
							break;
						case 1:
							a1 = (double)valuei * (double)valueo;
							break;
						default:
							break;
					}
*/
					num = num + a1;
					den = den + valuei;
//					printf("%d %d %f %f %f %f\n",ri1,ri2,valuei,valueo,num,den);
//					printf("%d %d %d %d %d %d\n",ri1,ri2,valuei,valueo,num,den);
				}
			}
			result = (den == 0) ? 0 : (num / den);
//			result = num / den;
/*
			break;
		default:

			break;  
	}
*/ 
	return result;
}

#endif

