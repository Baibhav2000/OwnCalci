#include <stdio.h>
#include <stdlib.h>
#include "BaseOps.h"
#include "NumberOps.h"

int maxBaseValue;

extern void deallocateNumber(Number n);

int main(){
	FILE *baseFile;

	char baseFileName[] = "../data/base.txt";

	baseFile = fopen(baseFileName, "r");

	maxBaseValue = initializeBase(baseFile);

	Number num = createNumber("18 12ab3");

	printNumber(num);
    

	fclose(baseFile);
	free(baseTable);
    deallocateNumber(num);

	return 0;
}
