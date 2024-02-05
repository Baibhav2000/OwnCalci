#ifndef DIGIT_H
#define DIGIT_H

struct Digit{
	int digitVal;
	struct Digit *next;
};

typedef struct Digit Digit;

#endif
