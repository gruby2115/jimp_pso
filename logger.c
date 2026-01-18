#include "logger.h"

void init_log_file(const char* plik) {
	FILE* f = fopen(plik, "w");
	if (f == NULL) {
		fprintf(stderr, "Nie udalo sie utworzyc pliku logow\n");
		return;
	}

	// Nagłówek CSV
	fprintf(f, "iteration,particle_id,x,y,value\n");

	fclose(f);
}

void log_swarm_state(const char* plik, Swarm* swarm, int it) {
	FILE* f = fopen(plik, "a");
	if (f == NULL) {
		return; // Jeśli nie można otworzyć, trudno, nie przerywamy symulacji
	}

	for (int i = 0; i < swarm->particle_count; i++) {
		Particle p = swarm->particles[i];

		// Zapisywanie: numeru iteracji, numeru cząstki, x, y, wartości sygnału
		fprintf(f, "%d,%d,%.4f,%.4f,%.4f\n", it, i, p.x, p.y, p.current_val);
	}

	fclose(f);
}
