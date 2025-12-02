#include "tBolsa.h"
#include <iostream>
#include <iomanip>

tFicha robar(tBolsa& bolsa) {
	int k, l, i = -1, j = -1;
	k = rand() % (NumColores * NumBarajas);
	l = rand() % NumFichas;


	if (!bolsa[k][l]) {
		i = k;
		j = l;
		if (l + 1 == NumFichas) {
			k = (k + 1) % (NumColores * NumBarajas);
		}
		l = (l + 1) % NumFichas;
		while (!bolsa[k][l] && (i != k || j != l)) {
			if (l + 1 == NumFichas) {
				k = (k + 1) % (NumColores * NumBarajas);
			}
			l = (l + 1) % NumFichas;
		}
	}

	tFicha ficha;

	if (i != k || j != l) {
		bolsa[k][l] = false;
		ficha = intToFicha(k, l);
		return ficha;
	}
	else {
		ficha.num = -1;
		return ficha;
	}
}

void mostrar(tBolsa const& bolsa) {
	std::cout << "Bolsa...\n";
	tFicha ficha;
	for (int i = 0; i < NumColores * NumBarajas; i++) {
		for (int j = 0; j < NumFichas; j++) {

			if (bolsa[i][j]) {
				ficha = intToFicha(i, j);
				std::cout << "  " << ficha;
			}
			else std::cout << " " << "-1";

		}
		std::cout << '\n';
	}
}

void inicializarBolsa(tBolsa& bolsa) {
	for (int i = 0; i < NumColores * NumBarajas; ++i) {
		for (int j = 0; j < NumFichas; ++j) {
			bolsa[i][j] = true;
		}
	}
}