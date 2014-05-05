/**
 * @file 	problem.c
 * @brief 	Example problem: Kozai.
 * @author 	Hanno Rein <hanno@hanno-rein.de>
 * @description	This example uses the IAS15 integrator to simulate
 * Kozai cycles of a planet perturbed by a distant star. The integrator
 * automatically adjusts the timestep so that even very high 
 * eccentricity encounters are resovled with high accuracy.
 *
 * 
 * @section 	LICENSE
 * Copyright (c) 2013 Hanno Rein, Dave Spiegel
 *
 * This file is part of rebound.
 *
 * rebound is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * rebound is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with rebound.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <time.h>
#include "main.h"
#include "tools.h"
#include "output.h"
#include "particle.h"
#include "integrator.h"

#ifdef OPENGL
extern int display_wire;
#endif // OPENGL

void problem_init(int argc, char* argv[]){
	// Setup constants
	dt 			= M_PI*1e-4; 	// initial timestep
	integrator_epsilon 	= 1e-8;		// accuracy patameter
	boxsize 		= 25;
	tmax			= 1.6e4;
#ifdef OPENGL
	display_wire	= 1; 			// show istantaneous orbits.
#endif // OPENGL
	init_box();

	// Initial conditions
	
	struct particle star; 
	star.m  = 1;
	star.x  = 0; star.y  = 0; star.z  = 0; 
	star.vx = 0; star.vy = 0; star.vz = 0;
	particles_add(star); 
	
	// The planet (a zero mass test particle)
	struct particle planet; 
	planet.m  = 0;
	double e_testparticle = 1.-1e-2;
	planet.x  = 1.-e_testparticle; planet.y  = 0; planet.z  = 0; 
	planet.vx = 0; planet.vy = sqrt((1.+e_testparticle)/(1.-e_testparticle)); planet.vz = 0;
	particles_add(planet); 
	
	tools_move_to_center_of_momentum();
	
	system("rm -v orbits.txt");		// delete previous output file
}

void problem_inloop(){
	if(output_check(4000.*dt)){		// outputs to the screen
		output_timing();
	}
	if(output_check(12.)){			// outputs to a file
		output_append_orbits("orbits.txt");
	}
}

void problem_output(){
	printf("%e\n",dt);
}

void problem_finish(){
}
