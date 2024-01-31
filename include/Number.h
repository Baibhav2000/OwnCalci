#ifndef NUMBER_H
#define NUMBER_H

typedef struct Digit{
		char digitValue;
		Digit *next;
}Digit;

typedef struct{
		int base;
		Digit *sequenceHeader;
}Number;

#endif

