/*
 * particle.h
 *
 *  Created on: 2015-11-05
 *      Author: mooshoo
 */

#ifndef PARTICLE_H_
#define PARTICLE_H_

#include "psoga.h"

class particle {
public:
	static const int sCategoryMatch[4][4];

	particle();
	virtual ~particle();

	static void CreateParticles( void );
	static void UpdateParticles( void );
	static void SetGlobalParticle(void);
	static void RemoveTaskFromMap(tProcessorMap* p_map, int task_id);
	static void AddTaskToMap(tProcessorMap* p_map, int task_id);
	static bool IsTaskInMap(tProcessorMap* p_map, int task_id);

	static tProcessorTaskMap* GetGlobalBestSchedule( void ) {
		return &sGlobalBestSchedule;
	}

private:
	static class particle* sParticleList[NUM_PARTICLES];
	static tProcessorTaskMap sGlobalBestSchedule;
	tProcessorTaskMap mLocalBestSchedule;
	tProcessorTaskMap mSchedule;

	void Update ( void );
	void CalculateMakespan(void);
	void SetLocalBestParticle(void);
	void MutationOperator(void);
	void CrossOverOperator(tProcessorTaskMap* p_map, tProcessorTaskMap* p_best_map);
};

#endif /* PARTICLE_H_ */
