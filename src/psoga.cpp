/*
 * psoga.cpp
 *
 *  Created on: 2015-11-05
 *      Author: Hasan
 */

#include "psoga.h"
#include "processor.h"
#include "particle.h"
#include "task.h"
#include <stdlib.h>
#include <time.h>

pso_ga::pso_ga() {
	srand(time(NULL));
	// Instantiate m processors
	processor::CreateProcessors();

	// Instantiate n tasks
	task::CreateTasks();

	// Instantiate p particles
	particle::CreateParticles();

	particle::SetGlobalParticle();
}

pso_ga::~pso_ga() {
	// TODO Auto-generated destructor stub
}

void pso_ga::run (void) {
	for (int i = 0; i < NUM_ITERATIONS; i++) {
		particle::UpdateParticles();
		particle::SetGlobalParticle();
	}
	int i = 0;
}

