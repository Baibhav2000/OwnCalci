#include "BaseOps.h"
#include <stdlib.h>
#include <string.h>

Base *baseTable;

int initializeBase(FILE *baseFile){
	baseTable = (Base*)malloc(sizeof(Base));

	char buffer[1024];

	fgets(buffer, sizeof(buffer), baseFile);

	int symbolsCount = 0;

	char *bufferPtr = buffer;

	while(*bufferPtr != '\0'){
		if(*bufferPtr != ' ')
			symbolsCount++;

		bufferPtr += 1;
	}

	baseTable->symbols = (char*)malloc(sizeof(char) * (symbolsCount+1));

	int symbolIdx = -1;

	bufferPtr = buffer;

	while(*bufferPtr != '\0'){
		if(*bufferPtr != ' '){
			symbolIdx += 1;
			baseTable->symbols[symbolIdx] = *bufferPtr;
		}

		bufferPtr += 1;
	}

	baseTable->symbols[symbolIdx] = '\0';
	baseTable->baseValue = symbolIdx;

	return baseTable->baseValue;
}

int lookup(char c){
	int digitCount = strlen(baseTable->symbols);

	for(int i=0; i < digitCount; i++){
		if(baseTable->symbols[i] == c)
			return i;
	}
	return -1;
}

