/*
 * processor.h
 *
 *  Created on: 2015-11-05
 *      Author: mooshoo
 */

#ifndef PROCESSOR_H_
#define PROCESSOR_H_

class processor {
public:
	processor();
	virtual ~processor();

private:
	int mProcessorSpeed;
	int mCommSpeed;
};

#endif /* PROCESSOR_H_ */
