/*
 * processor.cpp
 *
 *  Created on: 2015-11-05
 *      Author: mooshoo
 */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "processor.h"
#include "task.h"

class processor* processor::sProcessorList[NUM_PROCESSORS] = {0};
double processor::sAvgProcessorSpeed = 0;
double processor::sAvgCommSpeed = 0;

processor::processor() {
	mProcessorSpeed = rand() % PROCESSOR_SPEED_RANGE_SIZE + PROCESSOR_SPEED_RANGE_START; //10 to 3000 instructions per ms
	mCommSpeed = rand() % COMM_SPEED_RANGE_SIZE + COMM_SPEED_RANGE_START; //1 to 100 Bytes per ms
	mCategory = (enum eProcessorCategory) 0;
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

	for (int m = 0; m < NUM_PROCESSORS; m++) {
		sProcessorList[m]->DetermineCategory();
	}

	printf("\nCreated %d processors:\n", NUM_PROCESSORS);
	printf("   Avg Processor speed: %f instructions per ms\n", sAvgProcessorSpeed);
	printf("   Avg Communications speed: %f bytes per ms\n", sAvgCommSpeed);
}

class processor* processor::GetProccessor( int id ) {
	return (id >= 0 && id < NUM_PROCESSORS)? sProcessorList[id] : NULL;
}

double processor::GetTaskRunTime (class task* p_task) {
	double run_time;
	run_time = (p_task->GetTaskSize()/GetProcessorSpeed()) +
			(p_task->GetDataSize()/GetCommSpeed());
	return run_time;
}

void processor::DetermineCategory( void ) {
	if (mProcessorSpeed >= sAvgProcessorSpeed && mCommSpeed >= sAvgCommSpeed)
		mCategory = FASTER_PROCESSING_FASTER_COMM;
	else if (mProcessorSpeed >= sAvgProcessorSpeed && mCommSpeed < sAvgCommSpeed)
		mCategory = FASTER_PROCESSING_SLOWER_COMM;
	else if (mProcessorSpeed < sAvgProcessorSpeed && mCommSpeed >= sAvgCommSpeed)
		mCategory = SLOWER_PROCESSING_FASTER_COMM;
	else
		mCategory = SLOWER_PROCESSING_SLOWER_COMM;
}
