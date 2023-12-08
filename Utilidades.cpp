#include "Utilidades.h"

#include <cstdlib>

float Utilidades::randomf() {
    return rand() / (float) RAND_MAX;
}

bool Utilidades::chance(float chance, float dt) {
    return randomf() < dt * chance;
}
