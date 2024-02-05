#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "BaseOps.h"
#include "NumberOps.h"

extern int maxBaseValue;

Digit *addDigit(Digit *head, char ch, char *location){
	Digit *digit = (Digit*)malloc(sizeof(Digit));
	digit->digitVal = ch;
	digit->next = NULL;

	if(!head){
		head = digit;
		return head;
	}

	if(strcmp(location, "end") == 0){
		Digit *tmp = head;
		while(tmp->next)
			tmp = tmp->next;

		tmp->next = digit;
	}
	else if(strcmp(location, "begin") == 0){
		digit->next = head;
		head = digit;
	}

	return head;
}

Digit *deleteDigit(Digit *head){
	if(!head)
		return head;

	Digit *tmp = head;
	head = tmp->next;

	free(tmp);

	return head;
}

Number convert(Number n, int to_base){
	int base10Sequence = 0;

	int base10SequenceLength = 0;

	// Convert to base 10
	int count = n.digitCount - 1;
	int base = 10;

	Digit *tmp = n.sequenceHeader;

	while (tmp){
		int weightage = 1;

		for(int i=0; i<count; i++)
			weightage *= base;

		int val = weightage * lookup(tmp->digitVal);
		base10Sequence += val;
		tmp = tmp->next;
		count -= 1;
	}

	if(to_base == 10){
		Digit *base10 = NULL;
		int temp_val = base10Sequence;

		while(temp_val > 0){
			int r = temp_val % 10;
			base10SequenceLength++;
			base10 = addDigit(base10, baseTable->symbols[r], "begin");

			temp_val /= 10;
		}

		Number res;
		res.base = 10;
		res.sequenceHeader = base10;
		res.digitCount = base10SequenceLength;

		return res;
	}
	else{
		Number res;
		res.base = to_base;

		Digit *sequenceHeader = NULL;
		int digitLength = 0;

		int temp = base10Sequence;
		while(temp > 0){
			int r = temp % to_base;
			digitLength++;
			sequenceHeader = addDigit(sequenceHeader, baseTable->symbols[r], "begin");
		}

		res.digitCount = digitLength;
		res.sequenceHeader = sequenceHeader;

		return res;
	}
}

Number createNumber(char *number_format){
	Number num;

	char *copy = strdup(number_format);

	char **tokens = (char**)malloc(sizeof(char*) * 2);

	char* token = strtok(copy, " ");
	
	int idx = 0;
	while(token != NULL){
		tokens[idx] = (char*)malloc(sizeof(token));
		strcpy(tokens[idx], token);
		idx++;
		token = strtok(NULL, " ");
	}

	if(atoi(tokens[0]) > maxBaseValue){
		printf("ERROR : Given number beyond the maximum supported base (%d)\n",maxBaseValue);
		free(tokens[0]);
		free(tokens[1]);
		free(tokens);
		free(copy);
		exit(0);
	}

	num.base = atoi(tokens[0]);
	num.sequenceHeader = NULL;
	int count = 0;

	char *ptr = tokens[1];
	while(*ptr != '\0'){
		num.sequenceHeader = addDigit(num.sequenceHeader, *ptr, "end");
		count++;
		ptr++;
	}

	num.digitCount = count;

	free(tokens[0]);
	free(tokens[1]);
	free(tokens);
	free(copy);

	return num;
}

void printNumber(Number n){
	Digit *tmp = n.sequenceHeader;

	while(tmp){
		printf("%c",tmp->digitVal);
		
		tmp = tmp->next;
	}
	printf("\n");
}

void deallocateNumber(Number n){

	Digit *head = n.sequenceHeader;
	while(head){
		head = deleteDigit(head);
	}
}
