
#include <sys/types.h>
#include <malloc.h>
#include <stdint.h>

#define PR_SIZE 65536
//#define PR_SIZE 16384

class predictor {
private:
int *table;


public:
	predictor();
	~predictor();

	bool train(u_int32_t addr, char taken);

       
};
