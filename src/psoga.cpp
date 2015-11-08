/*
 * psoga.cpp
 *
 *  Created on: 2015-11-05
 *      Author: mooshoo
 */

#include "psoga.h"


pso_ga::pso_ga() {
	// Instantiate m processors
	processor::CreateProcessors();

	// Instantiate n tasks
	task::CreateTasks();

	// Instantiate p particles
	particle::CreateParticles();
}

pso_ga::~pso_ga() {
	// TODO Auto-generated destructor stub
}

void pso_ga::run (void) {
	for (int i = 0; i < NUM_ITERATIONS; i++) {
		for (int p = 0; p < NUM_PARTICLES; p++) {
			//Update particle

			//Update global particle
		}
	}
}

