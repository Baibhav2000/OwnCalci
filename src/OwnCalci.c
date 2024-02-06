#include <stdio.h>
#include <stdlib.h>
#include "BaseOps.h"
#include "NumberOps.h"

int maxBaseValue;

int main(){
	FILE *baseFile;

	char baseFileName[] = "../data/base.txt";

	baseFile = fopen(baseFileName, "r");

	maxBaseValue = initializeBase(baseFile);

	Number num1 = createNumber("16 73");
    Number num2 = createNumber("8 7");
    Number sum = add(num1, num2);

	printNumber(num1);
	printNumber(num2);
	printNumber(sum);

	fclose(baseFile);
	free(baseTable);

	return 0;
}
