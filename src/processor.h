/*
 * processor.h
 *
 *  Created on: 2015-11-05
 *      Author: mooshoo
 */

#include "psoga.h"

#ifndef PROCESSOR_H_
#define PROCESSOR_H_

enum {
	FASTER_PROCESSING_FASTER_COMM,
	FASTER_PROCESSING_SLOWER_COMM,
	SLOWER_PROCESSING_FASTER_COMM,
	SLOWER_PROCESSING_SLOWER_COMM,
} eProcessorCategory;

class processor {
public:
	processor();
	virtual ~processor();

	static void CreateProcessors();
	static class processor* GetProccessor( int id );
	static double GetAvgProcessorSpeed ( void ) { return sAvgProcessorSpeed;	}
	static double GetAvgCommSpeed ( void ) { return sAvgCommSpeed;	}

	double GetProcessorSpeed (void) { return mProcessorSpeed; }
	double GetCommSpeed (void) { return mCommSpeed; }
	double GetTaskRunTime (class task* p_task);
	void DetermineCategory( void );
	eProcessorCategory GetCategory (void) { return mCategory; }
private:
	static class processor* sProcessorList[NUM_PROCESSORS];
	static double sAvgProcessorSpeed;
	static double sAvgCommSpeed;
	double mProcessorSpeed;
	double mCommSpeed;
	eProcessorCategory mCategory;

};

#endif /* PROCESSOR_H_ */
