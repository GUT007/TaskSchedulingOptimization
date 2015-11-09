/*
 * processor.h
 *
 *  Created on: 2015-11-05
 *      Author: mooshoo
 */

#include "psoga.h"

#ifndef PROCESSOR_H_
#define PROCESSOR_H_

class processor {
public:
	processor();
	virtual ~processor();

	static void CreateProcessors();
	static class processor* GetProccessor( int id );
	static float GetAvgProcessorSpeed ( void ) { return sAvgProcessorSpeed;	}
	static float GetAvgCommSpeed ( void ) { return sAvgCommSpeed;	}

	float GetProcessorSpeed (void) { return mProcessorSpeed; }
	float GetCommSpeed (void) { return mCommSpeed; }
private:
	static class processor* sProcessorList[NUM_PROCESSORS];
	static float sAvgProcessorSpeed;
	static float sAvgCommSpeed;
	float mProcessorSpeed;
	float mCommSpeed;


};

#endif /* PROCESSOR_H_ */
