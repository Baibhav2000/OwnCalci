#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "BaseOps.h"
#include "NumberOps.h"

extern int maxBaseValue;

/*****************************************************
 * Function to insert digit
 *****************************************************/
Digit *addDigit(Digit *head, char ch, char *location){
	Digit *digit = (Digit*)malloc(sizeof(Digit));

	if(!digit){
		printf("ERROR: Failed to allocate memory for digit");
		exit(0);
	}

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


/*****************************************************
 * Function to delete digit
******************************************************/
Digit *deleteDigit(Digit *head){
	if(!head)
		return head;

	Digit *tmp = head;
	head = tmp->next;

	free(tmp);

	return head;
}

/**************************************************
 * Function to deallocate memory space
 * associated with a given number
***************************************************/
void deallocateNumber(Number n){

	Digit *head = n.sequenceHeader;
	while(head){
		head = deleteDigit(head);
	}
}


/****************************************************
 * Function to pad zeroes at the
 * front of a digit sequence
*****************************************************/
Digit *zeroPadding(Digit *header, int num_zeroes){
	while(num_zeroes > 0){
		header = addDigit(header, '0', "begin");
		num_zeroes--;
	}

	return header;
}


/***************************************************
 * Function to convert a number
 * to a given base
****************************************************/
Number convert(Number n, int to_base){
	int base10Sequence = 0;

	int base10SequenceLength = 0;

	// Convert to base 10
	int count = n.digitCount - 1;
	int base = n.base;

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

			temp /= to_base;
		}

		res.digitCount = digitLength;
		res.sequenceHeader = sequenceHeader;

		return res;
	}
}


/***************************************************
 * Function to create a number
****************************************************/
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
		if(*ptr >= baseTable->symbols[num.base]){
			printf("ERROR: Digit %c not a part of base %d\n",*ptr,num.base);
			deallocateNumber(num);
			exit(0);
		}
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


/***************************************************
 * Function to print a number
****************************************************/
void printNumber(Number n){
	Digit *tmp = n.sequenceHeader;

	while(tmp){
		printf("%c",tmp->digitVal);
		
		tmp = tmp->next;
	}
	printf("(%d)",n.base);
    deallocateNumber(n);
}


/*************************************************
 * Function to add two numbers
**************************************************/
Number add(Number a, Number b){

	/*******************************************
	 * Checking if their bases are equal or not
	********************************************/
	if(a.base == b.base){
		int max_base = a.base;

		// Check if their number of digits are equal or not 
		if(a.digitCount > b.digitCount){
			// Pad zeroes to the number having less digits
			int lenDiff = a.digitCount - b.digitCount;
			b.sequenceHeader = zeroPadding(b.sequenceHeader, lenDiff);
			b.digitCount = b.digitCount + lenDiff;
		}

		else if(a.digitCount < b.digitCount){
			// Pad zeroes to the number having less digits
			int lenDiff = b.digitCount - a.digitCount;
			a.sequenceHeader = zeroPadding(a.sequenceHeader, lenDiff);
			a.digitCount = a.digitCount + lenDiff;
		}

		Number sum;
		sum.base = max_base;
		sum.sequenceHeader = NULL;
		sum.digitCount = 0;

		Digit *tail1 = NULL, *tail2 = NULL;
		char sum_digit;
		int carry = 0;
		int digitCount = 0;

		while(tail1 != a.sequenceHeader && tail2 != b.sequenceHeader){
			Digit *t1 = a.sequenceHeader, *t2 = b.sequenceHeader;

			while(t1->next != tail1 && t2->next != tail2){
				t1 = t1->next;
				t2 = t2->next;
			}

			sum_digit = baseTable->symbols[(lookup(t1->digitVal) + lookup(t2->digitVal) + carry)  % max_base];
			sum.sequenceHeader = addDigit(sum.sequenceHeader, sum_digit, "begin");
			carry = (lookup(t1->digitVal) + lookup(t2->digitVal) + carry)  / max_base;
			digitCount++;

			tail1 = t1;
			tail2 = t2;
		}

		if(carry != 0){
			sum.sequenceHeader = addDigit(sum.sequenceHeader, baseTable->symbols[carry], "begin");
			digitCount++;
		}

		sum.digitCount = digitCount;

		return sum;
	}

	else if(a.base > b.base){
		int max_base = a.base;
		Number b_converted = convert(b, max_base);

		if(a.digitCount > b_converted.digitCount){
			int lenDiff = a.digitCount - b_converted.digitCount;
			b_converted.sequenceHeader = zeroPadding(b_converted.sequenceHeader, lenDiff);
			b_converted.digitCount = b_converted.digitCount + lenDiff;
		}

		else if(a.digitCount < b_converted.digitCount){
			int lenDiff = b_converted.digitCount - a.digitCount;
			a.sequenceHeader = zeroPadding(a.sequenceHeader, lenDiff);
			a.digitCount = a.digitCount + lenDiff;
		}

		Number sum;
		sum.base = max_base;
		sum.sequenceHeader = NULL;
		sum.digitCount = 0;

		Digit *tail1 = NULL, *tail2 = NULL;
		char sum_digit;
		int carry = 0;
		int digitCount = 0;

		while(tail1 != a.sequenceHeader && tail2 != b_converted.sequenceHeader){
			Digit *t1 = a.sequenceHeader, *t2 = b_converted.sequenceHeader;

			while(t1->next != tail1 && t2->next != tail2){
				t1 = t1->next;
				t2 = t2->next;
			}

			sum_digit = baseTable->symbols[(lookup(t1->digitVal) + lookup(t2->digitVal) + carry)  % max_base];
			sum.sequenceHeader = addDigit(sum.sequenceHeader, sum_digit, "begin");
			carry = (lookup(t1->digitVal) + lookup(t2->digitVal) + carry)  / max_base;
			digitCount++;

			tail1 = t1;
			tail2 = t2;
		}

		if(carry != 0){
			sum.sequenceHeader = addDigit(sum.sequenceHeader, baseTable->symbols[carry], "begin");
			digitCount++;
		}

		sum.digitCount = digitCount;

		deallocateNumber(b_converted);
		return sum;
	}

	else{
		int max_base = b.base;
		Number a_converted = convert(a, max_base);

		if(b.digitCount > a_converted.digitCount){
			int lenDiff = b.digitCount - a_converted.digitCount;
			a_converted.sequenceHeader = zeroPadding(a_converted.sequenceHeader, lenDiff);
			a_converted.digitCount = a_converted.digitCount + lenDiff;
		}

		else if(b.digitCount < a_converted.digitCount){
			int lenDiff = a_converted.digitCount - b.digitCount;
			b.sequenceHeader = zeroPadding(b.sequenceHeader, lenDiff);
			b.digitCount = b.digitCount + lenDiff;
		}

		Number sum;
		sum.base = max_base;
		sum.sequenceHeader = NULL;
		sum.digitCount = 0;

		Digit *tail1 = NULL, *tail2 = NULL;
		char sum_digit;
		int carry = 0;
		int digitCount = 0;

		while(tail1 != a_converted.sequenceHeader && tail2 != b.sequenceHeader){
			Digit *t1 = a_converted.sequenceHeader, *t2 = b.sequenceHeader;

			while(t1->next != tail1 && t2->next != tail2){
				t1 = t1->next;
				t2 = t2->next;
			}

			sum_digit = baseTable->symbols[(lookup(t1->digitVal) + lookup(t2->digitVal) + carry)  % max_base];
			sum.sequenceHeader = addDigit(sum.sequenceHeader, sum_digit, "begin");
			carry = (lookup(t1->digitVal) + lookup(t2->digitVal) + carry)  / max_base;
			digitCount++;

			tail1 = t1;
			tail2 = t2;
		}

		if(carry != 0){
			sum.sequenceHeader = addDigit(sum.sequenceHeader, baseTable->symbols[carry], "begin");
			digitCount++;
		}

		sum.digitCount = digitCount;

		deallocateNumber(a_converted);
		return sum;
	}

}

Number baseNComplement(Number n, int base){
	Number baseOneDownComplement;
	baseOneDownComplement.base = base;
	baseOneDownComplement.sequenceHeader = NULL;
	baseOneDownComplement.digitCount = n.digitCount;

	Digit *tmp = n.sequenceHeader;
	while(tmp){
		char digitVal = baseTable->symbols[lookup(baseTable->symbols[base-1]) - lookup(tmp->digitVal)];
		baseOneDownComplement.sequenceHeader = addDigit(baseOneDownComplement.sequenceHeader, digitVal, "end");
		tmp = tmp->next;
	}

	Number one;
	one.base = base;
	one.sequenceHeader = NULL;
	one.sequenceHeader = addDigit(one.sequenceHeader, baseTable->symbols[1], "end");
	one.digitCount = 1;

	Number BaseNComplement = add(baseOneDownComplement, one);

	deallocateNumber(baseOneDownComplement);

	return BaseNComplement;
}

Number subtract(Number a, Number b){

	if(a.base > b.base){
		Number b_converted = convert(b, a.base);

		Number b_complement = baseNComplement(b_converted, a.base);

		Number diff = add(a, b_complement);

		// Ignoring the carry digit
		diff.sequenceHeader = deleteDigit(diff.sequenceHeader); 
		while(diff.sequenceHeader->digitVal == '0'){
			diff.sequenceHeader = deleteDigit(diff.sequenceHeader);
		}

		deallocateNumber(b_complement);
		deallocateNumber(b_converted);

		return diff;
	}
	else if(a.base < b.base){
		Number a_converted = convert(a, b.base);
		Number b_complement = baseNComplement(b, b.base);

		Number diff = add(a, b_complement);

		// Ignoring the carry digit
		diff.sequenceHeader = deleteDigit(diff.sequenceHeader); 
		while(diff.sequenceHeader->digitVal == '0'){
			diff.sequenceHeader = deleteDigit(diff.sequenceHeader);
		}

		deallocateNumber(a_converted);
		deallocateNumber(b_complement);
		return diff;
	}

	else{
		Number b_complement = baseNComplement(b, b.base);

		Number diff = add(a, b_complement);

		// Ignoring the carry digit
		diff.sequenceHeader = deleteDigit(diff.sequenceHeader); 
		while(diff.sequenceHeader->digitVal == '0'){
			diff.sequenceHeader = deleteDigit(diff.sequenceHeader);
		}

		deallocateNumber(b_complement);
		return diff;
	}

}
