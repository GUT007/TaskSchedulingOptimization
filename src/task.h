/*
 * task.h
 *
 *  Created on: 2015-11-05
 *      Author: mooshoo
 */

#ifndef TASK_H_
#define TASK_H_

#include "psoga.h"

typedef enum eTaskCategory{
	MORE_INSTRUCTION_MORE_DATA,
	MORE_INSTRUCTION_LESS_DATA,
	LESS_INSTRUCTION_MORE_DATA,
	LESS_INSTRUCTION_LESS_DATA
} eTaskCategory;

class task {
public:
	task(int id);
	virtual ~task();

	double GetTaskSize (void) { return mInstructions; }
	double GetDataSize (void) { return mData; }

	static void CreateTasks();
	static class task* GetTask( int id );
	static double GetAvgInstructions ( void ) { return sAvgInstructions;	}
	static double GetAvgData ( void ) { return sAvgData;	}
	void DetermineCategory ( void );
	enum eTaskCategory GetCategory ( void ) {return mCategory;}
	int BetterProcessor (int p1_id, int p2_id);

private:
	static class task* sTaskList[NUM_TASKS];
	static double sAvgInstructions;
	static double sAvgData;
	int mID;
	double mInstructions;
	double mData;
	enum eTaskCategory mCategory;
};

#endif /* TASK_H_ */
