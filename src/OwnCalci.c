#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "BaseOps.h"
#include "NumberOps.h"

#define MAX_LINE_LENGTH 1024

int maxBaseValue;

extern void deallocateNumber(Number n);

int main(){
	FILE *baseFile;
    FILE *inputFile;
	char baseFileName[] = "../data/base.txt";
	char inputFileName[] = "../data/input.txt";

    char line[MAX_LINE_LENGTH];

	baseFile = fopen(baseFileName, "r");
	inputFile = fopen(inputFileName, "r");

	maxBaseValue = initializeBase(baseFile);

    int len;
    while(fgets(line, MAX_LINE_LENGTH, inputFile)){
        len = strlen(line);
        if(len > 0 && line[len - 1] == '\n')
            line[len - 1] = '\0';

        if(strcmp(line, "add") == 0){
            fgets(line, MAX_LINE_LENGTH, inputFile);
            len = strlen(line);
            if(len > 0 && line[len - 1] == '\n')
                line[len - 1] = '\0';

            Number num1 = createNumber(line);

            fgets(line, MAX_LINE_LENGTH, inputFile);
            len = strlen(line);
            if(len > 0 && line[len - 1] == '\n')
                line[len - 1] = '\0';

            Number num2 = createNumber(line);

            Number sum = add(num1, num2);

            printNumber(num1);
            printf(" + ");
            printNumber(num2);
            printf(" = ");
            printNumber(sum);
            printf("\n");

        }
        else if(strcmp(line, "subtract") == 0){
            fgets(line, MAX_LINE_LENGTH, inputFile);
            len = strlen(line);
            if(len > 0 && line[len - 1] == '\n')
                line[len - 1] = '\0';

            Number num1 = createNumber(line);

            fgets(line, MAX_LINE_LENGTH, inputFile);
            len = strlen(line);
            if(len > 0 && line[len - 1] == '\n')
                line[len - 1] = '\0';

            Number num2 = createNumber(line);

            Number difference = subtract(num1, num2);

            printNumber(num1);
            printf(" - ");
            printNumber(num2);
            printf(" = ");
            printNumber(difference);
            printf("\n");

        }
    }

	fclose(baseFile);
	fclose(inputFile);
	free(baseTable);

	return 0;
}
