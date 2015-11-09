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
	particle();
	virtual ~particle();

	static void CreateParticles( void );
	static void UpdateParticles( void );
	static void SetGlobalParticle(void);
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
};

#endif /* PARTICLE_H_ */
