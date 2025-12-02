#include "tSoporte.h"
#include <iostream>
#include <iomanip>

void ordenarPorNum(tSoporte& soporte) {
	tFicha aux;
	for (int i = 1; i < soporte.cont; i++) {
		for (int j = soporte.cont - 1; j >= i; j--) {
			if (soporte.fichas[j - 1].num > soporte.fichas[j].num) {
				aux = soporte.fichas[j - 1];
				soporte.fichas[j - 1] = soporte.fichas[j];
				soporte.fichas[j] = aux;
			}
			else if (soporte.fichas[i - 1].num == soporte.fichas[i].num) {
				if (compColorMayor(soporte.fichas[j - 1], soporte.fichas[j])) {
					aux = soporte.fichas[j - 1];
					soporte.fichas[j - 1] = soporte.fichas[j];
					soporte.fichas[j] = aux;
				}
			}
		}
	}
}

void ordenarPorColor(tSoporte& soporte) {
	tFicha aux;
	for (int i = 1; i < soporte.cont; ++i) {
		for (int j = soporte.cont - 1; j >= i; j--) {
			if (compColorMayor(soporte.fichas[j - 1], soporte.fichas[j])) {
				aux = soporte.fichas[j - 1];
				soporte.fichas[j - 1] = soporte.fichas[j];
				soporte.fichas[j] = aux;
			}
			else if (soporte.fichas[j - 1].color == soporte.fichas[j].color) {
				if (soporte.fichas[j - 1].num > soporte.fichas[j].num) {
					aux = soporte.fichas[j - 1];
					soporte.fichas[j - 1] = soporte.fichas[j];
					soporte.fichas[j] = aux;
				}
			}
		}
	}
}

void mostrar(const tSoporte& soporte) {
	std::cout << "Soporte:";
	for (int i = 0; i < soporte.cont; ++i) {
		std::cout << "  " << soporte.fichas[i];
	}
	std::cout << '\n';
}

void mostrarSeries(const tSoporte& soporte1) {
	tSoporte soporte;
	soporte.cont = soporte1.cont;
	for (int i = 0; i < soporte.cont; i++) {
		soporte.fichas[i] = soporte1.fichas[i];
	}

	int k = 1;
	ordenarPorNum(soporte);
	ordenarPorNum(soporte);
	tJugada jugada;
	jugada.cont = 1;
	jugada.fichas[0] = soporte.fichas[0];
	bool sirve = true;
	for (int i = 1; i < soporte.cont; i++) {
		sirve = true;
		if (soporte.fichas[i].num == jugada.fichas[0].num) {
			for (int j = 0; j < jugada.cont; j++) {
				if (soporte.fichas[i].color == jugada.fichas[j].color) {
					sirve = false;
				}
			}
			if (sirve) {
				jugada.fichas[jugada.cont] = soporte.fichas[i];
				jugada.cont++;
			}
		}
		else {
			if (jugada.cont >= 3) {
				std::cout << k << " - ";
				mostrar(jugada);
				std::cout << '\n';
				k++;
			}
			jugada.fichas[0] = soporte.fichas[i];
			jugada.cont = 1;
		}
	}
	if (jugada.cont >= 3) {
		std::cout << k << " - ";
		mostrar(jugada);
		std::cout << '\n';
		k++;
	}
	if (k == 1) {
		std::cout << "Ninguna\n";
	}
}

void mostrarEscaleras(const tSoporte& soporte1) {
	tSoporte soporte;
	soporte.cont = soporte1.cont;
	for (int i = 0; i < soporte.cont; i++) {
		soporte.fichas[i] = soporte1.fichas[i];
	}

	int k = 1;
	ordenarPorColor(soporte);
	ordenarPorColor(soporte);
	tJugada jugada;
	jugada.cont = 1;
	jugada.fichas[0] = soporte.fichas[0];
	for (int i = 1; i < soporte.cont; i++) {
		if (soporte.fichas[i].color == jugada.fichas[0].color && soporte.fichas[i].num == (jugada.fichas[jugada.cont - 1].num + 1)) {
			jugada.fichas[jugada.cont] = soporte.fichas[i];
			jugada.cont++;
		}
		else if (soporte.fichas[i].color == jugada.fichas[0].color && soporte.fichas[i].num == jugada.fichas[jugada.cont - 1].num);
		else {
			if (jugada.cont >= 3) {
				std::cout << k << " - ";
				mostrar(jugada);
				std::cout << '\n';
				k++;
			}
			jugada.fichas[0] = soporte.fichas[i];
			jugada.cont = 1;
		}
	}
	if (jugada.cont >= 3) {
		std::cout << k << " - ";
		mostrar(jugada);
		std::cout << '\n';
		k++;
	}
	if (k == 1) {
		std::cout << "Ninguna\n";
	}
}

void eliminaFichas(tSoporte& soporte, const tJugada& jugada) {
	for (int i = 0; i < jugada.cont; ++i) {
		int pos = buscar(soporte, jugada.fichas[i]);
		while (pos < soporte.cont - 1) {
			soporte.fichas[pos] = soporte.fichas[pos + 1];
			pos++;
		}
		soporte.cont--;
	}
}

bool nuevaJugada(tSoporte& soporte, tJugada& jugada) {
	std::cout << "     Fichas (0 al final): ";
	int posFicha, i = 0;
	std::cin >> posFicha;
	while (posFicha != 0) {
		jugada.fichas[i] = soporte.fichas[posFicha - 1];
		std::cin >> posFicha;
		i++;
	}
	jugada.cont  = i;

	mostrar(jugada);

	if (i == 2 || i > NumFichas || i == 0) return false;
	else return true;
}

int buscar(const tSoporte& soporte, const tFicha& ficha) {
	int i = 0;
	bool encontrado = false;
	while (i < soporte.cont && !encontrado) {
		if (soporte.fichas[i].color == ficha.color && soporte.fichas[i].num == ficha.num) encontrado = true;
		else i++;
	}
	if (!encontrado) return -1;
	else return i;
}