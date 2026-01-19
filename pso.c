#include <math.h>
#include "pso.h"

// Losowa liczba z zakresu [0, 1]
double random_01() {
	return (double)rand() / (double)RAND_MAX;
}

// Losowa pozycja na mapie
double random_coordinate(int rozmiar) {
	return random_01() * (double)rozmiar;
}

// Inicjalizacja roju
Swarm* init_swarm(int count, Map* mapa) {
	Swarm* swarm = (Swarm*)malloc(sizeof(Swarm));
	if (!swarm) return NULL;

	// Alokacja tablicy cząstek
	swarm->particles = (Particle*)malloc(sizeof(Particle) * count);
	if (!swarm->particles) {
		free(swarm);
		return NULL;
	}

	swarm->particle_count = count;
	swarm->gBest_val = 0;

	for (int i = 0; i < count; i++) {
		// Losowa pozycja startowa
		swarm->particles[i].x = random_coordinate(mapa->width - 1);
		swarm->particles[i].y = random_coordinate(mapa->height - 1);

		// Prędkość początkowa
		swarm->particles[i].vx = 0;
		swarm->particles[i].vy = 0;

		// Na początku pBest to aktualna pozycja
		swarm->particles[i].pBest_x = swarm->particles[i].x;
		swarm->particles[i].pBest_y = swarm->particles[i].y;
		swarm->particles[i].pBest_val = 0;
	}

	return swarm;
}

// Aktualizacja roju
void update_swarm(Swarm* swarm, Map* map, Parametry param) {
	for (int i = 0; i < swarm->particle_count; i++) {
		Particle* p = &swarm->particles[i];

		// Ocena funkcji celu (fitness function)
		double current_fitness = get_signal_value(map, p->x, p->y);
		p->current_val = current_fitness;

		// Aktualizacja pBest
		if (current_fitness > p->pBest_val) {
			p->pBest_val = current_fitness;
			p->pBest_x = p->x;
			p->pBest_y = p->y;
		}

		// Aktualizacja gBest
		if (current_fitness > swarm->gBest_val) {
			swarm->gBest_val = current_fitness;
			swarm->gBest_x = p->x;
			swarm->gBest_y = p->y;
		}

		// Obliczenie nowej prędkości 
		// v(t+1) = w*v + c1*r1*(pBest - x) + c2*r2*(gBest - x)
		double r1 = random_01();
		double r2 = random_01();

		p->vx = param.w * p->vx + param.c1 * r1 * (p->pBest_x - p->x) + param.c2 * r2 * (swarm->gBest_x - p->x);
		p->vy = param.w * p->vy + param.c1 * r1 * (p->pBest_y - p->y) + param.c2 * r2 * (swarm->gBest_y - p->y);

		// Obliczenie nowej pozycji 
		// x(t+1) = x(t) + v(t+1)
		p->x = p->x + p->vx;
		p->y = p->y + p->vy;
	}
}

// Zwolnienie pamięci 
void free_swarm(Swarm* swarm) {
	if (swarm) {
		if (swarm->particles) {
			free(swarm->particles);
		}
		free(swarm);
	}
}
