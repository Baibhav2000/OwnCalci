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

	Number num1 = createNumber("4 103");
    Number num2 = createNumber("3 12");
    Number sum = add(num1, num2);
    Number difference = subtract(num1, num2);

	printNumber(num1);
	printNumber(num2);
	printNumber(sum);
	printNumber(difference);

	fclose(baseFile);
	free(baseTable);

	return 0;
}
