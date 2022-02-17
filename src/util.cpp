#include "../include/util.h"
#include<stdlib.h>
#include<stdio.h>
void errif(bool condition, const char * mess){
    if(condition){
        perror("mess");
        exit(EXIT_FAILURE);
    }
}