#include <string.h>
#include <time.h>
#include "map.h"
#include "pso.h"
#include "logger.h" 

// Domyślne wartości parametrów
#define DEF_PARTICLES 30
#define DEF_ITERATIONS 100
#define DEF_FREQUENCY 0	// Czestotliwosc zapisu

// Domyślne wagi algorytmu
// w = 0.5, c1 = 1.0, c2 = 1.0
#define DEF_W 0.5
#define DEF_C1 1.0
#define DEF_C2 1.0

// Funkcja do wczytania konfiguracji z pliku
int load_config(const char* plik, Parametry* param) {
    FILE* f = fopen(plik, "r");
	if (f == NULL) return 0; // jeśli nie ma pliku, to wczytujemy domyślne

    // Zakładamy format pliku ajko trzy liczby oddzielone spacji
    if (fscanf(f, "%lf %lf %lf", &param->w, &param->c1, &param->c2) != 3) {
        fclose(f);
        return 0;
    }

    fclose(f);
    return 1;
}

int main(int argc, char* argv[]) {
	srand(time(NULL));

	// Sprawdzenie minimalnej liczby argumentów
	if (argc < 2) {
		fprintf(stderr, "Uzycie: <plik_mapy> [-p n] [-i n] [-c config] [-n log_step]\n");
		return 1;
	}

	// Ustawienie wartoœci domyœlnych
	char* map_file = argv[1];
	int particles_count = DEF_PARTICLES;
	int iterations = DEF_ITERATIONS;
	int log_interval = DEF_FREQUENCY;

	Parametry param;
	param.w = DEF_W;
	param.c1 = DEF_C1;
	param.c2 = DEF_C2;

	int i;

	for (i = 2; i < argc; i++) {
		if (strcmp(argv[i], "-p") == 0 && i + 1 < argc) {
			particles_count = atoi(argv[++i]);
		}
		else if (strcmp(argv[i], "-i") == 0 && i + 1 < argc) {
			iterations = atoi(argv[++i]);
		}
		else if (strcmp(argv[i], "-n") == 0 && i + 1 < argc) {
			log_interval = atoi(argv[++i]);
		}
		else if (strcmp(argv[i], "-c") == 0 && i + 1 < argc) {
			char* conf_file = argv[++i];
			if (!load_config(conf_file, &param)) {
				printf("Nie udalo sie wczytac pliku config: %s. Wczytywanie domyslnych.\n", conf_file);
			}
			else {
				printf("Wczytano parametry z pliku: w=%f, c1=%f, c2=%f\n", param.w, param.c1, param.c2);
			}	
		}
	}

	printf("Start symulacji: Mapa = %s, Czastki = %d, Iteracje = %d\n", map_file, particles_count, iterations);

	// Wczytanie mapy
	Map* map = load_map(map_file);
	if (!map) {
		return 1;
	}

	// Inicjalizacja roju
	Swarm* swarm = init_swarm(particles_count, map);
	if (!swarm) {
		fprintf(stderr, "Blad alokacji pamieci dla roju.\n");
		free_map(map);
		return 1;
	}

	// Przygotowanie pliku logów, jeśli użytkownik tego chce
	if (log_interval > 0) {
		init_log_file("pso_results.csv");
	}

	// Główna pętla symulacji
	for (i = 0; i < iterations; i++) {
		update_swarm(swarm, map, param);

		// Zapis postępów co n iteracji
		if (log_interval > 0 && (i % log_interval == 0)) {
			log_swarm_state("pso_results.csv", swarm, i);
		}
	}
	printf("\n");

	// Wynik koñcowy
	printf("WYNIKI:\n");
	printf("Pozycja (x, y): (%.4f, %.4f)\n", swarm->gBest_x, swarm->gBest_y);
	printf("Wartosc sygnalu: %.4f\n", swarm->gBest_val);

	// Sprz¹tanie pamiêci
	free_swarm(swarm);
	free_map(map);

	return 0;
}
