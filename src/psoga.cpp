/*
 * psoga.cpp
 *
 *  Created on: 2015-11-05
 *      Author: mooshoo
 */

#include "psoga.h"

pso_ga::pso_ga() {
	// Instantiate m processors
	for (int m = 0; m < NUM_PROCESSORS; m++) {
		mProcessor[m] = new processor();
	}

	// Instantiate n tasks
	for (int n = 0; n < NUM_TASKS; n++) {
		mTask[n] = new task();
	}

	// Instantiate p particles
	for (int p = 0; p < NUM_PARTICLES; p++) {
		mParticle[p] = new particle();
	}
	// Set global particle

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

