#ifndef TBOLSA_H
#define TBOLSA_H
#include "tFicha.h"

using tBolsa = bool[NumColores * NumBarajas][NumFichas];

tFicha robar(tBolsa& bolsa);
void mostrar(tBolsa const& bolsa);
void inicializarBolsa(tBolsa& bolsa);



#endif