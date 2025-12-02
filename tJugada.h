#ifndef TJUGADA_H
#define TJUGADA_H

#include "tFicha.h"

struct tJugada {
	tFicha fichas[NumFichas];
	int cont;
};

void mostrar(const tJugada& jugada);
int buscar(const tJugada& jugada, const tFicha& ficha);
int comprobarJug(tJugada& jugada);
bool ponerFicha(tJugada& jugada, tFicha& ficha);

#endif