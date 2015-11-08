/*
 * processor.cpp
 *
 *  Created on: 2015-11-05
 *      Author: mooshoo
 */

#include <stdlib.h>
#include <time.h>
#include "processor.h"

static class processor* processor::sProcessorList[NUM_PROCESSORS] = {0};
static float processor::sAvgProcessorSpeed = 0;
static float processor::sAvgCommSpeed = 0;

processor::processor() {
	srand(time(NULL));
	mProcessorSpeed = rand() % 3000000 + 100000;
	mCommSpeed = rand() % 100 + 1; //1 to 100 MBytes per second
}

processor::~processor() {
	// TODO Auto-generated destructor stub
}

static void processor::CreateProcessors( void ) {
	// Instantiate m processors
	for (int m = 0; m < NUM_PROCESSORS; m++) {
		sProcessorList[m] = new processor();
		sAvgProcessorSpeed += sProcessorList[m]->mProcessorSpeed;
		sAvgCommSpeed += sProcessorList[m]->mCommSpeed;
	}

	sAvgProcessorSpeed /= NUM_PROCESSORS;
	sAvgCommSpeed /= NUM_PROCESSORS;
}

static class proccessor* processor::GetProccessor( int id ) {
	return (id >= 0 && id < NUM_PROCESSORS)? sProcessorList[id] : NULL;
}
