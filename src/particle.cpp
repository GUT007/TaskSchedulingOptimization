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
const int particle::sCategoryMatch[4][4] =
{
	{MORE_INSTRUCTION_MORE_DATA, MORE_INSTRUCTION_LESS_DATA,
	LESS_INSTRUCTION_MORE_DATA, LESS_INSTRUCTION_LESS_DATA},
	{MORE_INSTRUCTION_LESS_DATA, MORE_INSTRUCTION_MORE_DATA,
	LESS_INSTRUCTION_LESS_DATA, LESS_INSTRUCTION_MORE_DATA},
	{LESS_INSTRUCTION_MORE_DATA, MORE_INSTRUCTION_MORE_DATA,
	LESS_INSTRUCTION_LESS_DATA, MORE_INSTRUCTION_LESS_DATA},
	{LESS_INSTRUCTION_LESS_DATA, MORE_INSTRUCTION_LESS_DATA,
	LESS_INSTRUCTION_MORE_DATA, MORE_INSTRUCTION_MORE_DATA}
};

particle::particle() {
	// Generate random schedule

	//Split the tasks between processors
	int task_per_processor = NUM_TASKS/NUM_PROCESSORS;
	int leftover_tasks = NUM_TASKS%NUM_PROCESSORS;

	for (int m = 0; m < NUM_PROCESSORS; m++) {

		mSchedule.processor_list[m].num_task = task_per_processor;
		if (leftover_tasks) {
			mSchedule.processor_list[m].num_task++;
			leftover_tasks--;
		}
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
	//cognitive term lambda1 times
	for (int i = 0; i < COGNITIVE_FACTOR; i++)
	{
		CrossOverOperator(&mSchedule, &mLocalBestSchedule);
	}

	//social term lambda2 times
	for (int i = 0; i < SOCIAL_FACTOR; i++) {
		CrossOverOperator(&mSchedule, &(particle::sGlobalBestSchedule));
	}

	//Inertia term omega times
	for (int i = 0; i < INERTIA_FACTOR; i++){
		MutationOperator();
	}

	CalculateMakespan();
	SetLocalBestParticle();
}

void particle::CrossOverOperator(tProcessorTaskMap* p_sch, tProcessorTaskMap* p_best_sch) {
	//Choose a random processor
	int random_p_id = rand() % NUM_PROCESSORS;
	tProcessorMap *p_map = &p_sch->processor_list[random_p_id];
	tProcessorMap *best_p_map = &p_best_sch->processor_list[random_p_id];
	processor * p_rand = processor::GetProccessor(random_p_id);
	enum eProcessorCategory p_cat = p_rand->GetCategory();

	//Get the processor to move from the chosen processor of best particle
	int num_task = best_p_map->num_task;
	int t_list[num_task];
	int task_count = 0;

	for (int c = 0; c < 4; c++) {
		enum eTaskCategory t_cat = (enum eTaskCategory) sCategoryMatch[p_cat][c];
		task_count = 0;
		//Go through all tasks and pick out the ones with the desired category
		for (int n = 0; n < num_task; n++) {
			//Get task and check its category. If category matches
			int t_id = best_p_map->task_id_list[n];
			task* t = task::GetTask(t_id);
			if (t->GetCategory() == t_cat && !IsTaskInMap(p_map, t_id)) {
				t_list[task_count++] = t_id;
			}
		}
		if (task_count) break;
	}

	if (task_count == 0 ) return;

	//get a random task from the shortlisted tasks
	int index = rand() % task_count;
	int gain_t_id = t_list[index];

	//Look for this task in p_sch. That is, check which processor currently has the task in p_sch
	tProcessorMap* p_src_map;
	for (int m = 0; m < NUM_PROCESSORS; m++) {
		if (IsTaskInMap(&(p_sch->processor_list[m]), gain_t_id)) {
			p_src_map = &p_sch->processor_list[m];
			break;
		}
	}

	//Get the task to lose from p_map
	num_task = p_map->num_task;
	int t1_list[num_task];
	task_count = 0;
	for (int c = 3; c >= 0; c--) {
		enum eTaskCategory t_cat = (enum eTaskCategory) sCategoryMatch[p_cat][c];
		task_count = 0;
		//Go through all tasks and pick out the ones with the desired category
		for (int n = 0; n < num_task; n++) {
			//Get task and check its category. If category matches
			int t_id = p_map->task_id_list[n];
			task* t = task::GetTask(t_id);
			if (t->GetCategory() == t_cat) {
				t1_list[task_count++] = t_id;
			}
		}
		if (task_count) break;
	}

	//get a random task from the shortlisted tasks
	index = rand() % task_count;
	int lose_t_id = t1_list[index];

	//Now swap the tasks between the processors in p_sch
	RemoveTaskFromMap(p_src_map, gain_t_id);
	AddTaskToMap(p_map, gain_t_id);
	RemoveTaskFromMap(p_map, lose_t_id);
	AddTaskToMap(p_src_map, lose_t_id);
}

void particle::MutationOperator( void ) {
	//Get two random processors
	int random_p1_id, random_p2_id, gaining_p_id, losing_p_id;
	class processor *gaining_p, *losing_p;
	double p1_rt, p2_rt, losing_rt, gaining_rt;
	tProcessorMap *gaining_pmap, *losing_pmap;

	random_p1_id = rand() % NUM_PROCESSORS;
	do {
		random_p2_id = rand() % NUM_PROCESSORS;
	} while (random_p1_id == random_p2_id);

	//Compare run time to select which processor will gain/lose a task
	p1_rt = mSchedule.processor_list[random_p1_id].run_time;
	p2_rt = mSchedule.processor_list[random_p2_id].run_time;

	if (p1_rt > p2_rt) {
		gaining_p_id = random_p2_id;
		losing_p_id = random_p1_id;
		gaining_rt = p2_rt;
		losing_rt = p1_rt;
	} else {
		gaining_p_id = random_p1_id;
		losing_p_id = random_p2_id;
		gaining_rt = p1_rt;
		losing_rt = p2_rt;
	}

	gaining_pmap = (tProcessorMap *)&mSchedule.processor_list[gaining_p_id];
	losing_pmap = (tProcessorMap *)&mSchedule.processor_list[losing_p_id];

	gaining_p = processor::GetProccessor(gaining_p_id);
	losing_p = processor::GetProccessor(losing_p_id);

	//Select which process will be moved from losing p to gaining p
	int num_task = mSchedule.processor_list[losing_p_id].num_task;
	double rt_diff = losing_rt - gaining_rt;
	int moved_task_id = -1;
	for (int n = 0; n < num_task; n++) {
		class task* p_task = task::GetTask(losing_pmap->task_id_list[n]);
		double task_rt_losing_p = losing_p->GetTaskRunTime(p_task);
		double task_rt_gaining_p = gaining_p->GetTaskRunTime(p_task);
		double new_losing_rt = losing_rt - task_rt_losing_p;
		double new_gaining_rt = gaining_rt + task_rt_gaining_p;
		double new_rt_diff = (new_losing_rt < new_gaining_rt)? (new_gaining_rt - new_losing_rt) : (new_losing_rt - new_gaining_rt);
		if (new_rt_diff < rt_diff) {
			rt_diff = new_rt_diff;
			moved_task_id = losing_pmap->task_id_list[n];
		}
	}
	if (moved_task_id != -1) {
		RemoveTaskFromMap(losing_pmap, moved_task_id);
		AddTaskToMap(gaining_pmap, moved_task_id);
	}
	moved_task_id = -1;
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
			mSchedule.processor_list[m].run_time += p_processor->GetTaskRunTime(p_task);
		}

		//Set makespan to the largest run time
		if (mSchedule.makespan == 0 || mSchedule.processor_list[m].run_time > mSchedule.makespan) {
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
		if (particle::sGlobalBestSchedule.makespan == 0 ||
			p_particle->mLocalBestSchedule.makespan < particle::sGlobalBestSchedule.makespan) {
			memcpy(&(particle::sGlobalBestSchedule), &(p_particle->mLocalBestSchedule), sizeof(tProcessorTaskMap));
		}
	}
}

void particle::CreateParticles( void ) {
	for (int p = 0; p < NUM_PARTICLES; p++) {
		sParticleList[p] = new particle();
	}
	printf("Created %d particles:\n", NUM_PARTICLES);

}

void particle::UpdateParticles( void ) {
	for (int p = 0; p < NUM_PARTICLES; p++) {
		sParticleList[p]->Update();
	}
}

//Utility Functions
void particle::RemoveTaskFromMap(tProcessorMap* p_map, int task_id) {
	int num_task = p_map->num_task;
	bool task_found = false;
	for (int n = 0; n < num_task-1; n++) {
		 if (p_map->task_id_list[n] == task_id) task_found = true;
		 if (task_found) p_map->task_id_list[n] = p_map->task_id_list[n+1];
	}
	p_map->num_task--;
}

void particle::AddTaskToMap(tProcessorMap* p_map, int task_id) {
	int num_task = p_map->num_task++;
	p_map->task_id_list[num_task] = task_id;
}

bool particle::IsTaskInMap(tProcessorMap* p_map, int task_id) {
	int num_task = p_map->num_task;
	for (int n = 0; n < num_task; n++) {
		if (p_map->task_id_list[n] == task_id) return true;
	}

	return false;
}
