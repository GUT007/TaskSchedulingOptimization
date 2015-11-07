/*
 * task.cpp
 *
 *  Created on: 2015-11-05
 *      Author: mooshoo
 */

#include <stdlib.h>
#include <time.h>
#include "task.h"


task::task() {
	srand(time(NULL));
	mInstructions = rand() % 10000000 + 100;
	mData = rand() % 100000;
}

task::~task() {
	// TODO Auto-generated destructor stub
}

