#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

struct TwoInts { int int0; int int1; };

void* fnc (void* vPtr);

int main() {
	pthread_t			tId;
	struct		TwoInts		twoInts;
	twoInts.int0 = 2; 	twoInts.int1 = 3;
	pthread_create(&tId, NULL, fnc, (void*)&twoInts);
	int*	intPtr;
	pthread_join(tId, (void**)&intPtr);
	printf("the sum is %d\n", *intPtr);
	return(EXIT_SUCCESS);
}

void* fnc (void* vPtr) {
	static 		int		sum;
	struct		TwoInts*	twoIntsPtr;
	
	twoIntsPtr = (struct	TwoInts*) vPtr;
	sum = twoIntsPtr->int0 + twoIntsPtr->int1;
	return( (void*)&sum );
}
