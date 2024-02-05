#ifndef NUMBER_H
#define NUMBER_H

#include "Digit.h"

typedef struct{
		int base, digitCount;
		Digit *sequenceHeader;
}Number;

#endif

