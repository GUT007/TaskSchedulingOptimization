/*
 * particle.cpp
 *
 *  Created on: 2015-11-05
 *      Author: mooshoo
 */

#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdio.h>
#include "particle.h"
#include "processor.h"
#include "task.h"

class particle* particle::sParticleList[NUM_PARTICLES] = {0};
tProcessorTaskMap particle::sGlobalBestSchedule = {0};

particle::particle() {
	// Generate random schedule

	//Split the tasks between processors
	int task_per_processor = NUM_TASKS/NUM_PROCESSORS;
	int leftover_tasks = NUM_TASKS%NUM_PROCESSORS;

	for (int m = 0; m < NUM_PROCESSORS; m++) {

		mSchedule.processor_list[m].num_task = task_per_processor;
		if (leftover_tasks--) mSchedule.processor_list[m].num_task++;
	}

	//Randomly assign tasks to processors
	int task_id_list[NUM_TASKS];
	leftover_tasks = NUM_TASKS;
	for (int n = 0; n < NUM_TASKS; n++) task_id_list[n] = n;

	for (int m = 0; m < NUM_PROCESSORS-1; m++) {
		int num_tasks = mSchedule.processor_list[m].num_task;
		for (int n = 0; n < num_tasks; n++) {
			int task_id = rand() % leftover_tasks;
			mSchedule.processor_list[m].task_id_list[n] = task_id_list[task_id];
			for (int j = task_id; j < leftover_tasks; j++) task_id_list[j] = task_id_list[j+1];
			leftover_tasks--;
		}
	}

	//Assign the rest of the tasks to the last processor
	int num_tasks = mSchedule.processor_list[NUM_PROCESSORS-1].num_task;
	for (int n = 0; n < num_tasks; n++) {
		mSchedule.processor_list[NUM_PROCESSORS-1].task_id_list[n] = task_id_list[n];
	}

	//Calculate Makespan
	CalculateMakespan();

	//Set current schedule to local best schedule
	memcpy(&mLocalBestSchedule, &mSchedule, sizeof(tProcessorTaskMap));
}

particle::~particle() {
	// TODO Auto-generated destructor stub
}

void particle::Update (void) {
	//MutationOperator();
	//CrossOverOperator();
	CalculateMakespan();
	SetLocalBestParticle();
}

void particle::CalculateMakespan(void) {
	mSchedule.makespan = 0;
	for (int m = 0; m < NUM_PROCESSORS; m++) {
		int num_tasks = mSchedule.processor_list[m].num_task;
		mSchedule.processor_list[m].run_time = 0;
		processor* p_processor = processor::GetProccessor(m);

		//Add up the run times of all assigned tasks
		for (int n = 0; n < num_tasks; n++) {
			task* p_task = task::GetTask(mSchedule.processor_list[m].task_id_list[n]);
			mSchedule.processor_list[m].run_time += ((p_task->GetTaskSize()/p_processor->GetProcessorSpeed()) +
													( p_task->GetDataSize()/ p_processor->GetCommSpeed()) );
		}

		//Set makespan to the smallest run time
		if (mSchedule.processor_list[m].run_time < mSchedule.makespan) {
			mSchedule.makespan = mSchedule.processor_list[m].run_time;
		}
	}
}

void particle::SetLocalBestParticle( void ) {
	if (mSchedule.makespan < mLocalBestSchedule.makespan) {
		memcpy(&mLocalBestSchedule, &mSchedule, sizeof(tProcessorTaskMap));
	}
}

//Static functions
void particle::SetGlobalParticle( void ) {
	for (int p = 0; p < NUM_PARTICLES; p++) {
		particle* p_particle = sParticleList[p];
		if (p_particle->mLocalBestSchedule.makespan < particle::sGlobalBestSchedule.makespan) {
			memcpy(&(particle::sGlobalBestSchedule), &(p_particle->mLocalBestSchedule), sizeof(tProcessorTaskMap));
		}
	}
}

void particle::CreateParticles( void ) {
	for (int p = 0; p < NUM_PARTICLES; p++) {
		sParticleList[p] = new particle();
	}
}

void particle::UpdateParticles( void ) {
	for (int p = 0; p < NUM_PARTICLES; p++) {
		sParticleList[p]->Update();
	}
}


