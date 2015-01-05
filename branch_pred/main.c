#define INCLUDEPRED
#include <stdlib.h>
#include <string.h>
#include <stdio.h>	
#include <sys/types.h>

#include <fstream>
#include <iostream>
#include "./predictor.h"





int main(int argc, char* argv[]) {
FILE* _trace; // trace file
u_int64_t pc, cycles_since_last;
char taken;
char temp_string[200];
u_int64_t hit=0,inst=0,branch=0;

	if(argc != 2) {
		printf("Usage: %s [trace file]\n",argv[0]);
		return 1;
	}
	

	
	snprintf(temp_string,200,"xz -dc %s",argv[1]);
	_trace = popen(temp_string,"r");
	predictor predict;
	
	while (fscanf(_trace, "%lx %c %ld\n",&pc,&taken,&cycles_since_last) == 3)
	{
//	printf("%lx %c %ld\n",pc, taken, cycles_since_last);
	branch++;
//	printf("BRANCHES	%ld\n",branch);
	if(predict.train(pc,taken)) 
	{
		hit++;
//		printf("PREDICT		%ld\n",hit);
        }
	inst=inst+cycles_since_last;
	}
printf("INSTRUCTION	%ld\n",inst);
printf("BRANCHES	%ld\n",branch);
printf("PREDICT		%ld\n",hit);
pclose(_trace);
}
