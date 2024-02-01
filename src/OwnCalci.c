#include <stdio.h>
#include "BaseOps.h"
#include <stdlib.h>

int main(){
	FILE *baseFile;

	char baseFileName[] = "../data/base.txt";

	baseFile = fopen(baseFileName, "r");

	int maxBaseValue = initializeBase(baseFile);

	printf("Max. Base Value : %d\n",maxBaseValue);

	char symbol = 'g';

	printf("Value of the symbol %c : %d\n",symbol, lookup(symbol));

	fclose(baseFile);
	free(baseTable);

	return 0;
}
