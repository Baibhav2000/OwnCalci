#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "BaseOps.h"
#include "NumberOps.h"

Digit *addDigit(Digit *head, char ch){
    Digit *digit = (Digit*)malloc(sizeof(Digit));
    digit->digitVal = ch;
    digit->next = NULL;

    if(!head){
        head = digit;
        return head;
    }

    Digit *tmp = head;
    while(tmp->next)
        tmp = tmp->next;

    tmp->next = digit;

    return head;
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

    num.base = atoi(tokens[0]);
    num.sequenceHeader = NULL;

    char *ptr = tokens[1];
    while(*ptr != '\0'){
        num.sequenceHeader = addDigit(num.sequenceHeader, *ptr);
        ptr++;
    }

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
