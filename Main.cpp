#include <iostream>
#include <iomanip>
#include <fstream>
#include "tColor.h"
#include "tFicha.h"
#include "tSoporte.h"
#include "tBolsa.h"
#include "tJugada.h"

const int MaxJugadores = 4, IniFichas = 7, MaxJugadas = NumFichas * NumColores;

struct ArraySoportes {
	tSoporte soportes [MaxJugadores];
	int cont;
};

struct tTablero {
	tJugada jugada[MaxJugadas];
	int cont;
};

struct tOpciones {
	int jugOpc[MaxJugadas];
	int jugCont = 0;
};

void mostrar(const tTablero& tablero) {
	std::cout << "Tablero: \n";
	if (tablero.cont == 0) std::cout << "No hay jugadas\n";
	for (int i = 0; i < tablero.cont; i++) {
		std::cout << i + 1 << ": ";
		for (int j = 0; j < tablero.jugada[i].cont; j++) {
			//std::cout << colorToStr(tablero.jugada[i].fichas[j].color) << ' ' << tablero.jugada[i].fichas[j].num << ' ';
			std::cout << "   " << tablero.jugada[i].fichas[j];
		}
		std::cout << '\n';
	}
}

void repartir(tBolsa& bolsa, ArraySoportes& arraysoportes) {
	tFicha ficha = { rojo, 0};
	for (int i = 0; i < MaxJugadores; i++) {
		arraysoportes.soportes[i].cont = 0;
		while (ficha.num != -1 && arraysoportes.soportes[i].cont < IniFichas) {
			ficha = robar(bolsa);
			if (ficha.num != -1) {
				arraysoportes.soportes[i].fichas[arraysoportes.soportes[i].cont] = ficha;
				arraysoportes.soportes[i].cont++;
			}
		}
	}
}

bool jugar(tTablero& tablero, tSoporte& soporte) {
	mostrar(soporte);
	std::cout << "        ";
	for (int i = 1; i < soporte.cont + 1; i++) {
		std::cout << std::setw(3) << i;
	}
	std::cout << "\n\n";
	tJugada jugada;
	bool jugOk = nuevaJugada(soporte, jugada);

	if (!jugOk) {
		std::cout << "Jugada erronea. Volviendo al menu...\n\n";
		return false;
	}
	else{
		std::cout << "  -  ";
		int typeJug = comprobarJug(jugada);
		int selecOp;
		bool no_robar = true;
		switch (typeJug) {
			case 1: { //Ficha individual
				tOpciones opciones;
				opciones.jugCont = 0;
				std::cout << "Posiciones del tablero donde poner la ficha: ";

				for (int i = 0; i < tablero.cont; i++) {
					bool jugOk = ponerFicha(tablero.jugada[i], jugada.fichas[0]);
					if (jugOk) {
						opciones.jugOpc[opciones.jugCont] = i;
						opciones.jugCont++;
					}
				}
				for (int i = 0; i < opciones.jugCont; i++) {
					std::cout << opciones.jugOpc[i] + 1 << ' ';
				}
				std::cout << "\n\n";

				if (opciones.jugCont == 0) {
					std::cout << "No hay posiciones disponibles para esa ficha. Volviendo al menu...\n\n";
					no_robar = false;
				} else {
					/*if (opciones.jugCont == 1) {
						selecOp = opciones.jugOpc[0];
						std::cout << "Seleccione en que jugada desea poner la ficha: ";
						std::cout << selecOp;

					}
					else {*/
					bool valido = false;
						std::cout << "Seleccione en que jugada desea poner la ficha: ";
						std::cin >> selecOp;

						selecOp--;

						while (!valido) {
							for (int k = 0; k < opciones.jugCont && !valido; k++) {
								if (selecOp == opciones.jugOpc[k]) {
									valido = true;
								}
							}
							if (!valido) {
								std::cout << "\nOpcion no valida, introduzca otra: ";
								std::cin >> selecOp;
								selecOp--;
							}
						}
					//}

					if (jugada.fichas[0].num == tablero.jugada[selecOp].fichas[tablero.jugada[selecOp].cont - 1].num + 1)
						tablero.jugada[selecOp].fichas[tablero.jugada[selecOp].cont] = jugada.fichas[0];
					
					else if (jugada.fichas[0].num == tablero.jugada[selecOp].fichas[tablero.jugada[selecOp].cont - 1].num)
						tablero.jugada[selecOp].fichas[tablero.jugada[selecOp].cont] = jugada.fichas[0];
				
					else if(jugada.fichas[0].num == tablero.jugada[selecOp].fichas[0].num - 1){
						for (int i = tablero.jugada[selecOp].cont; i > 0; i--) {
							tablero.jugada[selecOp].fichas[i] = tablero.jugada[selecOp].fichas[i - 1];
						}
						tablero.jugada[selecOp].fichas[0] = jugada.fichas[0];
					}

					tablero.jugada[selecOp].cont++;
					eliminaFichas(soporte, jugada);
					mostrar(tablero);
					std::cout << '\n';
				}
				break;
			}
			case 2: { //Escalera
				std::cout << "Escalera correcta!\n\n";

				for (int i = 0; i < jugada.cont; i++) {
					tablero.jugada[tablero.cont].fichas[i] = jugada.fichas[i];
				}

				tablero.jugada[tablero.cont].cont = jugada.cont;
				tablero.cont++;
				eliminaFichas(soporte, jugada);
				mostrar(tablero);
				std::cout << '\n';
				break;
			}
			case 3: { //Serie
				std::cout << "Serie correcta!\n\n";
				for (int i = 0; i < jugada.cont; i++) {
					tablero.jugada[tablero.cont].fichas[i] = jugada.fichas[i];
				}
				tablero.jugada[tablero.cont].cont = jugada.cont;
				tablero.cont++;
				eliminaFichas(soporte, jugada);
				mostrar(tablero);
				std::cout << '\n';
				break;
			}
			case 4: { //Jugada no v�lida
				std::cout << "No es una jugada correcta!Prueba de nuevo...\n\n";
				no_robar = false;
				break;
			}
		}
		return no_robar;
	}
}

int menu() {
	int opcion;
	std::cout << "1: Ordenar por num., 2: Ordenar por color, 3: Sugerir, 4: Poner, 0: Fin >>> ";
	std::cin >> opcion;
	while (opcion < 0 || opcion > 4) {
		std::cout << "Opcion no valida, por favor introduzca otra >>> ";
		std::cin >> opcion;
	}
	return opcion;
}

int juego(tBolsa& bolsa, ArraySoportes& arraysoportes, tTablero tablero) {
	inicializarBolsa(bolsa);
	bool bolsa_vacia = false;
	std::cout << "\nRepartiendo fichas...\n\n";
	repartir(bolsa, arraysoportes);
	int jug_actual = rand() % MaxJugadores;

	bool ganador = false;
	int opcion = -1;
	int pasa_turno = 0;
	bool robas;
	while(!ganador && (!bolsa_vacia || pasa_turno < 4)){
		robas = true;
		mostrar(bolsa);
		std::cout << "\n\nTurno para el jugador " << jug_actual + 1 << " ...\n\n";
		mostrar(tablero);
		std::cout << '\n';
		mostrar(arraysoportes.soportes[jug_actual]);
		opcion = menu();
		while (opcion != 0) {
			switch (opcion){
				case 1: {
					ordenarPorNum(arraysoportes.soportes[jug_actual]);
					ordenarPorNum(arraysoportes.soportes[jug_actual]);
					std::cout << '\n';
					break;
				}
				case 2: {
					ordenarPorColor(arraysoportes.soportes[jug_actual]);
					ordenarPorColor(arraysoportes.soportes[jug_actual]);
					std::cout << '\n';
					break;
				}
				case 3: {
					std::cout << "Series disponibles: \n";
					mostrarSeries(arraysoportes.soportes[jug_actual]);
					std::cout << "Escaleras disponibles: \n";
					mostrarEscaleras(arraysoportes.soportes[jug_actual]);
					std::cout << '\n';
					break;
				}
				case 4: {
					if(robas) robas = !jugar(tablero, arraysoportes.soportes[jug_actual]);
					else {
						jugar(tablero, arraysoportes.soportes[jug_actual]);
					}
					break;
				}
			}

			if (arraysoportes.soportes[jug_actual].cont == 0) {
				ganador = true;
				opcion = 0;
			}
			else {
				mostrar(arraysoportes.soportes[jug_actual]);
				opcion = menu();
			}
		}

		if (robas && arraysoportes.soportes[jug_actual].cont < MaxFichas) {
			tFicha ficha;
			ficha = robar(bolsa);
			if(ficha.num != -1){
				arraysoportes.soportes[jug_actual].fichas[arraysoportes.soportes[jug_actual].cont] = ficha;
				arraysoportes.soportes[jug_actual].cont++;
				mostrar(arraysoportes.soportes[jug_actual]);
				std::cout << "\n";
			}
			else {
				bolsa_vacia = true;
			}
		}
		if(robas && bolsa_vacia) pasa_turno++;
		else pasa_turno = 0;

		if (!ganador && pasa_turno < 4) jug_actual = (jug_actual + 1) % MaxJugadores;
	}
	return jug_actual;
}

int main() {
	srand(time(NULL));
	ArraySoportes arraysoportes;
	arraysoportes.cont = MaxJugadores;
	tBolsa bolsa;
	tTablero tablero;
	int ganador;
	tablero.cont = 0;
	std::cout << "NORMAS: (No son opcionales)\n - 4 Jugadores \n - Hay fichas numeradas del 1 al " << NumFichas << "\n - Se reparten " << IniFichas << " fichas al empezar\n\n-----------EMPEZAR JUEGO-----------\n\n";
	system("pause");
	ganador = juego(bolsa, arraysoportes, tablero);
	if(ganador == -1){
		int puntos[MaxJugadores] = { 0, 0, 0, 0 };
		for (int i = 0; i < arraysoportes.cont; i++) {
			for (int j = 0; j < arraysoportes.soportes[i].cont; j++) {
				puntos[i] += arraysoportes.soportes[i].fichas[j].num;
			}
		}
		ganador = 0;
		for (int i = 0; i < arraysoportes.cont; i++) {
			if (puntos[ganador] > puntos[i]) ganador = i;
		}
	}
	std::cout << "\n\n\nEl ganador del juego ha sido el jugador " << ganador + 1 << ". Enhorabuena!!!";
	
	return 0;
}