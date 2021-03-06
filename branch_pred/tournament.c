
#include "predictor.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

predictor::predictor() {
	table = new int[PR_SIZE];
       gtable = new int[PR_SIZE];         // Prediction table for 2 to 10 bit global register

	for (int i=0; i<PR_SIZE;i++)
	{
	        table[i] = 7;
	        gtable[i] = 3;
	}
        globalReg = 0;
}


predictor::~predictor() { 
printf("Calling destructor");
delete [] table; 
delete [] gtable
;}//free (table); free(gtable);}


bool predictor::train(u_int32_t addr,  char taken){

int index = addr % PR_SIZE;
int hash1 = index ^ (globalReg & 1023);
//int hash2 = index ^ (globalReg % 1023);
int hash2 = globalReg ^ (index & 1023);
bool hit =0;
//printf("Hash1 : %d, Hash2 : %d, Index : %d, globalReg : %d \n",hash1, hash2, index, globalReg);

hit=tournamentPred(gtable[index], table[index] % 4, gtable[(index ^ globalReg) & 1023] % 4, taken);
//predictor2bit(gtable, (index) ^ (globalReg % 1023), taken);
predictor2bit(gtable, hash2, taken);
predictor2bit(table,index,taken);

        globalReg = globalReg << 1;
        if (taken == 'T') {
            globalReg++;
        }
        globalReg &= 1023; //Keep global register to 10 bits

return hit;
}


bool predictor::predictor2bit(int * table, int index, char taken) {
    bool correct = 0;
    assert(index< PR_SIZE);
    int state = table[index] % 4;
    if (taken == 'T') {
        switch (state) {
            case 0:
            case 1:
                table[index]++;
                break;
            case 2:
                table[index]++;
//		correct=1;
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
  //              correct = 1;
            case 2:
            case 3:
                table[index]--;
                break;
        }
    }
    return correct;
}

/**
 * Tournament Predictor
 * Update the entry in selector base on the actual branch direction
 * (11 - Strongly Prefer 2 bits Bimodal, 10 - Weakly Prefer 2 bits Bimodal, 
 *  01 - Weakly Prefer Gshare, 00 - Strongly Prefer Gshare)
 *
 * @param entry entry of the selector
 * @param bPred prediction made by 2 bits Bimodal
 * @param gPred prediction made by Gshare
 * @return whether entry in the prefered table matches actual branch direction
 */

bool predictor::tournamentPred(int &entry, int bPred, int gPred, char taken) {
    bool correct = 0;
    int state = entry & 12;
    if (taken == 'T') {
        switch (state) {
            case 0:
            case 4:
                if (gPred >= 2) {
                    if (bPred <= 1) {
                        entry = entry % 4;
                    }
                    correct = 1;
                } else if (bPred > 1) {
                    entry += 4;
                }
                break;
            case 8:
            case 12:
                if (bPred >= 2) {
                    if (gPred <= 1) {
                        entry = 12 + entry % 4;
                    }
                    correct = 1;
                } else if (gPred >= 2) {
                    entry -= 4;
                }
                break;
        }
    } else {
        switch (state) {
            case 0:
            case 4:
                if (gPred <= 1) {
                    if (bPred >= 2) {
                        entry = entry % 4;
                    }
                    correct = 1;
                } else if (bPred <= 1) {
                    entry += 4;
                }
                break;
            case 8:
            case 12:
                if (bPred <= 1) {
                    if (gPred >= 2) {
                        entry = 12 + entry % 4;
                    }
                    correct = 1;
                } else if (bPred > 1 && gPred <= 1) {
                    entry -= 4;
                }
                break;
        }
    }
    return correct;
}
