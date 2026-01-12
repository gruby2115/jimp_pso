#ifndef MAP_H
#define MAP_H

#include <stdio.h>
#include <stdlib.h>

// Struktura mapy
typedef struct {
    int width;
    int height;
    double** signal; // Tablica alokowana dynamicznie
} Map;

Map* load_map(char* file);
double get_signal_value(Map* map, double x, double y);
void free_map(Map* map);

#endif