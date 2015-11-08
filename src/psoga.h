/*
 * psoga.h
 *
 *  Created on: 2015-11-05
 *      Author: mooshoo
 */

#ifndef PSOGA_H_
#define PSOGA_H_

#define INTERTIA_FACTOR			2		//omega
#define COGNITIVE_FACTOR		3		//lambda1
#define SOCIAL_FACTOR			4		//lambda2
#define	NUM_PARTICLES			10  	//p
#define NUM_ITERATIONS			50		//i
#define NUM_PROCESSORS			10		//m
#define NUM_TASKS				100		//n

typedef struct {
	int 		num_task;
	float 		run_time;
	int			task_id_list[NUM_TASKS];
} tProcessorMap;

typedef struct {
	tProcessorMap 	processor_list[NUM_PROCESSORS];
	float			makespan;
} tProcessorTaskMap;

class pso_ga {
public:
	pso_ga();
	virtual ~pso_ga();
	void run ();
};

#endif /* PSOGA_H_ */
