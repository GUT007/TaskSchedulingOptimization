/*
 * task.h
 *
 *  Created on: 2015-11-05
 *      Author: mooshoo
 */

#ifndef TASK_H_
#define TASK_H_

class task {
public:
	task();
	virtual ~task();
private:
	int mInstructions;
	int mData;
};

#endif /* TASK_H_ */
