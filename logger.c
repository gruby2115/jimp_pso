#include "logger.h"

void init_log_file(const char* filename) {
    FILE* f = fopen(filename, "w"); // Tryb "w" czyœci plik jeœli istnia³
    if (f == NULL) {
        perror("Nie udalo sie utworzyc pliku logow");
        return;
    }

    // Nag³ówek CSV
    fprintf(f, "iteration,particle_id,x,y,value\n");

    fclose(f);
}

void log_swarm_state(const char* filename, Swarm* swarm, int it) {
    FILE* f = fopen(filename, "a"); // Tryb "a" dopisuje na koñcu pliku
    if (f == NULL) {
        return; // Jeœli nie mo¿na otworzyæ, trudno, nie przerywamy symulacji
    }

    for (int i = 0; i < swarm->particle_count; i++) {
        Particle p = swarm->particles[i];

        // Zapisujemy: numer iteracji, numer cz¹stki, x, y, wartoœæ sygna³u
        fprintf(f, "%d,%d,%.4f,%.4f,%.4f\n", it, i, p.x, p.y, p.current_val);
    }

    fclose(f);
}