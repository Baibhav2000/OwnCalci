#include <stdio.h>
#include <stdlib.h>
#include "BaseOps.h"
#include "NumberOps.h"

int main(){
	FILE *baseFile;

	char baseFileName[] = "../data/base.txt";

	baseFile = fopen(baseFileName, "r");

	int maxBaseValue = initializeBase(baseFile);

    Number num = createNumber("18 12ab3");

    printNumber(num);

	fclose(baseFile);
	free(baseTable);

	return 0;
}
