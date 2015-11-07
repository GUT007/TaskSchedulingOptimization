/*
 * processor.cpp
 *
 *  Created on: 2015-11-05
 *      Author: mooshoo
 */

#include <stdlib.h>
#include <time.h>
#include "processor.h"


processor::processor() {
	srand(time(NULL));
	mProcessorSpeed = rand() % 3000000 + 100000;
	mCommSpeed = rand() % 100 + 1; //1 to 100 MBytes per second
}

processor::~processor() {
	// TODO Auto-generated destructor stub
}

