#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

// Variables globales
float avg_value;
int min_value;
int max_value;
int numArray[50];

int main(){
    for (int i = 0 ; i<50 ; i++ ){
        numArray[i] = rand() % 100;
        printf("numArray[%i] = %i\n", i,numArray[i]);
    }
    return 0;
}