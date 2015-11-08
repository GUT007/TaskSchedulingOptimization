/*
 * task.cpp
 *
 *  Created on: 2015-11-05
 *      Author: mooshoo
 */

#include <stdlib.h>
#include <time.h>
#include "task.h"


task::task(int id) {
	srand(time(NULL));
	mID = id;
	mInstructions = rand() % 10000000 + 100;
	mData = rand() % 100000;
}

task::~task() {
	// TODO Auto-generated destructor stub
}

static void task::CreateTasks( void ) {
	// Instantiate n tasks
	for (int n = 0; n < NUM_TASKS; n++) {
		sTaskList[n] = new task(n);
		sAvgInstructions += sTaskList[n]->mInstructions;
		sAvgData += sTaskList[n]->mData;
	}

	sAvgInstructions /= NUM_TASKS;
	sAvgData /= NUM_TASKS;
}

static class task* task::GetTask( int id ) {
	return (id >= 0 && id < NUM_TASKS)? sTaskList[id] : NULL;
}
