#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>
#include <stdlib.h>
#include "pso.h"

// Tworzy plik i wpisuje nag³ówek CSV
void init_log_file(const char* plik);

// Dopisuje aktualne pozycje wszystkich cz¹stek do pliku
void log_swarm_state(const char* plik, Swarm* swarm, int it);

#endif
