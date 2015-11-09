/*
 * task.cpp
 *
 *  Created on: 2015-11-05
 *      Author: mooshoo
 */

#include <stdlib.h>
#include <time.h>
#include "task.h"

class task* task::sTaskList[NUM_TASKS] = {0};
float task::sAvgInstructions = 0;
float task::sAvgData = 0;

task::task(int id) {
	mID = id;
	mInstructions = rand() % TASK_INSTRUCTION_RANGE_SIZE + TASK_INSTRUCTION_RANGE_START;
	mData = rand() % TASK_DATA_RANGE_SIZE + TASK_DATA_RANGE_START;
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
}

class task* task::GetTask( int id ) {
	return (id >= 0 && id < NUM_TASKS)? sTaskList[id] : NULL;
}
