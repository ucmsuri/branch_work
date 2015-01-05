/*
#define INCLUDEPRED

#include "predictor.h"
#include <stdio.h>
#include <sys/types.h>

//#define IS_BR_CONDITIONAL 1

bool predictor::train(u_int32_t addr,  char taken){

bool hit =0;
hit=predict_brcond (addr, IS_BR_CONDITIONAL );

FetchHistoryUpdate (addr, IS_BR_CONDITIONAL ,taken,1);

update_brcond (addr, IS_BR_CONDITIONAL ,taken,1);
return hit;
}

*/
