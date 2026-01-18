#ifndef MAP_H
#define MAP_H

#include <stdio.h>
#include <stdlib.h>

// Struktura mapy
typedef struct {
	int width;
	int height;
	double** signal; // Tablica sygnałów
} Map;

Map* load_map(char* plik);
double get_signal_value(Map* map, double x, double y);
void free_map(Map* map);


#endif
