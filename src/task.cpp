/*
 * task.cpp
 *
 *  Created on: 2015-11-05
 *      Author: mooshoo
 */

#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "task.h"

class task* task::sTaskList[NUM_TASKS] = {0};
double task::sAvgInstructions = 0;
double task::sAvgData = 0;

task::task(int id) {
	mID = id;
	long long rnd;
	rnd = rand()*rand();
	mInstructions = rnd % TASK_INSTRUCTION_RANGE_SIZE + TASK_INSTRUCTION_RANGE_START;
	rnd = rand()*rand();
	mData = rnd % TASK_DATA_RANGE_SIZE + TASK_DATA_RANGE_START;
	mCategory = MORE_INSTRUCTION_MORE_DATA;
}

task::~task() {
	// TODO Auto-generated destructor stub
}

void task::CreateTasks( void ) {
	// Instantiate n tasks
	for (int n = 0; n < NUM_TASKS; n++) {
		sTaskList[n] = new task(n);
		sAvgInstructions += sTaskList[n]->mInstructions;
		sAvgData += sTaskList[n]->mData;
	}

	sAvgInstructions /= NUM_TASKS;
	sAvgData /= NUM_TASKS;

	for (int n = 0; n < NUM_TASKS; n++) {
		sTaskList[n]->DetermineCategory();
	}

	printf("\nCreated %d tasks:\n", NUM_TASKS);
	printf("   Avg number of instructions: %f \n", sAvgInstructions);
	printf("   Avg Comm Data: %f bytes\n", sAvgData);
}

class task* task::GetTask( int id ) {
	return (id >= 0 && id < NUM_TASKS)? sTaskList[id] : NULL;
}

void task::DetermineCategory ( void ) {
	if (mInstructions >= sAvgInstructions && mData >= sAvgData)
		mCategory = MORE_INSTRUCTION_MORE_DATA;
	else if (mInstructions >= sAvgInstructions && mData < sAvgData)
		mCategory = MORE_INSTRUCTION_LESS_DATA;
	else if (mInstructions < sAvgInstructions && mData >= sAvgData)
		mCategory = LESS_INSTRUCTION_MORE_DATA;
	else
		mCategory = LESS_INSTRUCTION_LESS_DATA;
}





