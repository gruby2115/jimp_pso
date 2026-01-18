#include "map.h"

#define KARA -10000.0

Map* load_map(char* plik) {
	FILE* file = fopen(plik, "r");
	if (!plik) {
		fprintf(stderr, "Nie udalo sie otworzyc pliku mapy");
		return NULL;
	}

	int w, h;
	// Odczyt wymiarów
	if (fscanf(plik, "%d %d", &w, &h) != 2) {
		fprintf(stderr, "Blad formatu naglowka mapy\n");
		fclose(plik);
		return NULL;
	}

	// Alokacja struktury
	Map* map = (Map*)malloc(sizeof(Map));
	if (!map) {
		fclose(plik);
		return NULL;
	}
	map->width = w;
	map->height = h;

	// Dynamiczna alokacja tablicy sygnałów
	map->signal = (double**)malloc(h * sizeof(double*));
	if (!map->signal) {
		free(map);
		fclose(plik);
		return NULL;
	}

	for (int i = 0; i < h; i++) {
		map->signal[i] = (double*)malloc(w * sizeof(double));
		if (!map->signal[i]) {
			for (int j = 0; j < i; j++)
				free(map->signal[j]);
			free(map->signal);
			free(map);
			fclose(plik);
			return NULL;
		}
	}

	// Wczytywanie wartości
	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			if (fscanf(plik, "%lf", &map->signal[y][x]) != 1) {
				fprintf(stderr, "Blad odczytu danych mapy w wierszu %d\n", y);
				fclose(plik);
				return NULL;
			}
		}
	}

	fclose(file);
	return map;
}

double get_signal_value(Map* map, double x, double y) {
	// Rzutowanie pozycji (x, y) na indeksy całkowite
	int ix = (int)x;
	int iy = (int)y;

	// Obsługa wyjścia poza zakres
	if (ix < 0 || ix >= map->width || iy < 0 || iy >= map->height) {
		return KARA;
	}

	return map->signal[iy][ix];
}

void free_map(Map* map) {
	if (map) {
		if (map->signal) {
			for (int i = 0; i < map->height; i++) {
				if (map->signal[i]) {
					free(map->signal[i]);
				}
			}
			free(map->signal);
		}
		free(map);
	}
}
