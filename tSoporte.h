#ifndef TSOPORTE_H
#define TSOPORTE_H

#include "tFicha.h"
#include "tJugada.h"

const int MaxFichas = 50;

struct tSoporte {
	tFicha fichas[MaxFichas];
	int cont;
};

void ordenarPorNum(tSoporte& soporte);
void ordenarPorColor(tSoporte& soporte);
void mostrar(const tSoporte& soporte);
void mostrarSeries(const tSoporte& soporte);
void mostrarEscaleras(const tSoporte& soporte1);
void eliminaFichas(tSoporte& soporte, const tJugada& jugada);
bool nuevaJugada(tSoporte& soporte, tJugada& jugada);
int buscar(const tSoporte& soporte, const tFicha& ficha);

#endif