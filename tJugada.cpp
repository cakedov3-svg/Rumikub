#include "tJugada.h"
#include <iostream>
#include <iomanip>

void mostrar(const tJugada& jugada) {
	for (int i = 0; i < jugada.cont; i++) {
		std::cout << "   " << jugada.fichas[i];
	}
}

int buscar(const tJugada& jugada, const tFicha& ficha) {
	int i = 0;
	bool encontrado = false;
	while (i < jugada.cont && !encontrado) {
		if (jugada.fichas[i].color == ficha.color && jugada.fichas[i].num == ficha.num) encontrado = true;
		i++;
	}
	if (!encontrado) return -1;
	else return i;
}

int comprobarJug(tJugada& jugada) {
	int opc = 0;
	if (jugada.cont == 1) opc = 1; //Ficha individual
	else {
		int i = 0, j = 0;
		bool escOk = true, serieOk = true;

		//Escalera
		while (i < jugada.cont - 1 && escOk) {
			if (jugada.fichas[i].num != jugada.fichas[i + 1].num - 1 || jugada.fichas[i].color != jugada.fichas[i + 1].color) escOk = false;
			i++;
		}

		//Serie
		bool colorCompr[NumColores];
		for (int i = 0; i < NumColores; i++) {
			colorCompr[i] = false;
		}
		while (j < jugada.cont - 1 && serieOk) {
			if (jugada.fichas[j].num != jugada.fichas[j + 1].num || colorCompr[jugada.fichas[j].color]) serieOk = false;
			if (!colorCompr[jugada.fichas[j].color]) colorCompr[jugada.fichas[j].color] = true;
			++j;
		}

		//Comprobar opcion
		if (escOk) opc = 2;
		else if (serieOk) opc = 3;
		else opc = 4;
	}
	return opc;
}

bool ponerFicha(tJugada& jugada, tFicha& ficha) {
	//Comprobar Escalera
	if (((ficha.num == jugada.fichas[0].num - 1 && ficha.color == jugada.fichas[0].color) || (ficha.num == jugada.fichas[jugada.cont - 1].num + 1 && ficha.color == jugada.fichas[jugada.cont - 1].color)) && (jugada.fichas[0].num == jugada.fichas[1].num - 1)) return true;

	//Comprobar Serie
	bool colorCompr[NumColores];
	for (int i = 0; i < NumColores; i++) {
		colorCompr[i] = false;
	}
	for (int i = 0; i < jugada.cont; i++) {
		colorCompr[jugada.fichas[i].color] = true;
	}
	if (ficha.num == jugada.fichas[0].num && jugada.fichas[0].color != jugada.fichas[1].color && !colorCompr[ficha.color]) return true;

	return false;
}