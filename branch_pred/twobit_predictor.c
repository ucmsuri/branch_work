

#include "predictor.h"
#include <stdio.h>

predictor::predictor() {
	table = new int[PR_SIZE];
	for (int i=0; i<PR_SIZE;i++)
	{
	        table[i] = 7; 
	}
}

predictor::~predictor() { free (table);}

bool predictor::train(u_int32_t addr, char taken) {
    bool correct = 0;
    int index=addr%PR_SIZE;
    int state = table[index] % 4;
//printf("b4_Index :%d , taken %c, table[Index] %d, Hit %d \n",index,taken,table[index],correct); 
    if (taken == 'T') {
        switch (state) {
            case 0:
            case 1:
                table[index]++;
                break;
            case 2:
                table[index]++;
            case 3:
                correct = 1;
                break;
        }
    } else {
        switch (state) {
            case 0:
                correct = 1;
                break;
            case 1:
            //    correct = 1;
            case 2:
            case 3:
                table[index]--;
                break;
        }
    }
//printf("Af_Index :%d , taken %c, table[Index] %d, Hit %d \n",index,taken,table[index],correct); 
    return correct;
}

