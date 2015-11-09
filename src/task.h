/*
 * task.h
 *
 *  Created on: 2015-11-05
 *      Author: mooshoo
 */

#ifndef TASK_H_
#define TASK_H_

#include "psoga.h"

class task {
public:
	task(int id);
	virtual ~task();

	float GetTaskSize (void) { return mInstructions; }
	float GetDataSize (void) { return mData; }

	static void CreateTasks();
	static class task* GetTask( int id );
	static float GetAvgInstructions ( void ) { return sAvgInstructions;	}
	static float GetAvgData ( void ) { return sAvgData;	}

private:
	static class task* sTaskList[NUM_TASKS];
	static float sAvgInstructions;
	static float sAvgData;
	int mID;
	float mInstructions;
	float mData;
};

#endif /* TASK_H_ */
