/*
 * processor.cpp
 *
 *  Created on: 2015-11-05
 *      Author: mooshoo
 */

#include <stdlib.h>
#include <time.h>
#include "processor.h"

class processor* processor::sProcessorList[NUM_PROCESSORS] = {0};
float processor::sAvgProcessorSpeed = 0;
float processor::sAvgCommSpeed = 0;

processor::processor() {
	mProcessorSpeed = rand() % PROCESSOR_SPEED_RANGE_SIZE + PROCESSOR_SPEED_RANGE_START; //10 to 3000 instructions per ms
	mCommSpeed = rand() % COMM_SPEED_RANGE_SIZE + COMM_SPEED_RANGE_START; //1 to 100 Bytes per ms
}

processor::~processor() {
	// TODO Auto-generated destructor stub
}

void processor::CreateProcessors( void ) {
	// Instantiate m processors
	for (int m = 0; m < NUM_PROCESSORS; m++) {
		sProcessorList[m] = new processor();
		sAvgProcessorSpeed += sProcessorList[m]->mProcessorSpeed;
		sAvgCommSpeed += sProcessorList[m]->mCommSpeed;
	}

	sAvgProcessorSpeed /= NUM_PROCESSORS;
	sAvgCommSpeed /= NUM_PROCESSORS;
}

class processor* processor::GetProccessor( int id ) {
	return (id >= 0 && id < NUM_PROCESSORS)? sProcessorList[id] : NULL;
}
