
#include <sys/types.h>
#include <malloc.h>
#include <stdint.h>

//#define PR_SIZE 32768
#define PR_SIZE 16348

class predictor {
private:
int *table;
int *gtable;
int globalReg;

public:
	predictor();
	~predictor();

	bool train(u_int32_t addr, char taken);
        bool tournamentPred(int &entry, int bPred, int gPred, char taken);
        bool predictor2bit(int * table, int index, char taken); 
};
