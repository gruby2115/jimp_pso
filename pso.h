#ifndef PSO_H
#define PSO_H

#include <stdlib.h>
#include <stdio.h>
#include "map.h"

// Struktura pojedynczej cząstki
typedef struct {
	double x, y;	// Aktualna pozycja
	double vx, vy;	// Aktualna prędkość
	double pBest_x, pBest_y; // Najlepsza pozycja znaleziona przez drona
	double pBest_val;	// Wartość sygnału w pBest
	double current_val;	// Aktualna wartość sygnału
} Particle;

// Struktura roju
typedef struct {
	Particle* particles;	// Tablica dynamiczna cząstek
	int particle_count;
	double gBest_x, gBest_y;	// Najlepsza pozycja znaleziona przez rój
	double gBest_val;	// Wartość sygnału w gBest
} Swarm;

// Parametry PSO
typedef struct {
	double w;	// Współczynnik bezwładności
	double c1;	// Współczynnik poznawczy
	double c2;	// Współczynnik społeczny
}Parametry;

// Funkcje PSO
Swarm* init_swarm(int count, Map* mapa);
void update_swarm(Swarm* swarm, Map* mapa, Parametry param);
void free_swarm(Swarm* swarm);

#endif
