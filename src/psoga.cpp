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
#include <stdio.h>

pso_ga::pso_ga() {
	srand(RANDOM_SEED);
	// Instantiate m processors
	processor::CreateProcessors();

	// Instantiate n tasks
	task::CreateTasks();

	srand(time(NULL));

	// Instantiate p particles
	particle::CreateParticles();

	particle::SetGlobalParticle();

	printf("Initial Best Makespan: %f min\n", (particle::GetGlobalBestSchedule()->makespan)/60000);
}

pso_ga::~pso_ga() {
	// TODO Auto-generated destructor stub
}

void pso_ga::run (void) {
	int i = 0;
	for (i = 0; i < NUM_ITERATIONS; i++) {
		particle::UpdateParticles();
		particle::SetGlobalParticle();
		if (i % 50 == 0)
		printf("Iteration: %d     Makespan: %f min\n", i, (particle::GetGlobalBestSchedule()->makespan)/60000);
	}
	printf("Iteration: %d     Makespan: %f min\n", i, (particle::GetGlobalBestSchedule()->makespan)/60000);
}

