#include "stdio.h"
#include <mpi.h>

#define maxtime 100000

#define MINPROC 4
#define cols 200
#define totrows 200
/* rows de cada processo*/
#define rows totrows/MINPROC + 2

double black[rows+2][cols+2]

void storeconst(int s, int e, int row, int col, double val) {
	if (row >= s && rows <= e)
		black[row-s][col] =val;}


