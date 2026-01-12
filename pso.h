#ifndef PSO_H
#define PSO_H

#include <stdlib.h>
#include <stdio.h>
#include "map.h"

// Struktura pojedynczej cz¹stki
typedef struct {
    double x, y;          // Aktualna pozycja
    double vx, vy;        // Aktualna prêdkoœæ
    double pBest_x, pBest_y; // Najlepsza pozycja znaleziona przez drona
    double pBest_val;     // Wartoœæ sygna³u w pBest
    double current_val;   // Aktualna wartoœæ sygna³u
} Particle;

// Struktura roju
typedef struct {
    Particle* particles;  // Tablica dynamiczna cz¹stek
    int particle_count;
    double gBest_x, gBest_y; // Najlepsza pozycja znaleziona przez rój
    double gBest_val;     // Wartoœæ sygna³u w gBest
} Swarm;

// Parametry PSO
typedef struct {
	double w;      // Wspó³czynnik bezw³adnoœci
	double c1;     // Wspó³czynnik poznawczy
	double c2;     // Wspó³czynnik spo³eczny
}Parametry;

// Funkcje PSO
Swarm* init_swarm(int count, Map* mapa);
void update_swarm(Swarm* swarm, Map* mapa, Parametry param);
void free_swarm(Swarm* swarm);

#endif