//============================================================================
// Name        : pso_ga.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <stdio.h>
#include "psoga.h"
using namespace std;

int main() {
	printf("TASK SCHEDULING OPTIMIZATION USING PSO AND GA\n\n");
	pso_ga* pso_ga_opt = new pso_ga();
	pso_ga_opt->run();
	return 0;
}
