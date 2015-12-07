/*
 * psoga.h
 *
 *  Created on: 2015-11-05
 *      Author: mooshoo
 */

#ifndef PSOGA_H_
#define PSOGA_H_

#define INERTIA_FACTOR			2		//omega
#define COGNITIVE_FACTOR		3		//lambda1
#define SOCIAL_FACTOR			4		//lambda2
#define	NUM_PARTICLES			10  	//p
#define NUM_ITERATIONS			50		//i
#define NUM_PROCESSORS			10		//m
#define NUM_TASKS				100		//n

//Randomize Processor speed between 10 to 3010 instructions per ms
#define PROCESSOR_SPEED_RANGE_SIZE			3000
#define PROCESSOR_SPEED_RANGE_START			10

//Randomize Processor comm speed between 10 to 100000 bytes per ms
#define COMM_SPEED_RANGE_SIZE				100000
#define COMM_SPEED_RANGE_START 				10

//Randomize Task avg instructions between 100 to 1000000000 instructions
#define TASK_INSTRUCTION_RANGE_SIZE			1000000000
#define TASK_INSTRUCTION_RANGE_START		100

//Randomize task data between 0 to 100000 bytes
#define TASK_DATA_RANGE_SIZE				100000
#define TASK_DATA_RANGE_START				0

typedef struct {
	int 		num_task;
	double 		run_time;
	int			task_id_list[NUM_TASKS];
} tProcessorMap;

typedef struct {
	tProcessorMap 	processor_list[NUM_PROCESSORS];
	double			makespan;
} tProcessorTaskMap;

class pso_ga {
public:
	pso_ga();
	virtual ~pso_ga();
	void run (void);
};

#endif /* PSOGA_H_ */
