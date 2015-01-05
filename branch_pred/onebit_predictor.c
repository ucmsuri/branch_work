
#include "predictor.h"
#include <stdio.h>

predictor::predictor() {
	table = new int[PR_SIZE];
	for (int i=0; i<PR_SIZE;i++)
	{
	        table[i] = 1; 
	}
}

predictor::~predictor() { free (table);}

bool predictor::train(u_int32_t addr, char taken) {
bool correct = 0;
int index=addr%PR_SIZE;
//    printf("Index :%d , taken %c, table[Index] %d, b4_Hit %d \n",index,taken,table[index],correct); 
    if (taken == 'T') {
        if (table[index] >= 1) {
            correct = 1;
        } else {
            table[index] += 1;
        }
    } else {
        if (table[index] < 1) {
            correct = 1;
        } else {
            table[index] -= 1;
        }
    }
  //  printf("Index :%d , taken %c, table[Index] %d, Af_Hit %d \n",index,taken,table[index],correct); 
    return correct;


}
