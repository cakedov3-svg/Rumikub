#include "tFicha.h"
#include <iostream>

bool compColorMayor(tFicha const& fichai, tFicha const& fichad) {
	if (int(fichai.color) > int(fichad.color)) return true;
	else return false;
}

tFicha intToFicha(int k, int l) {
	tFicha ficha;
	ficha.num = l;
	ficha.color = tColor(k % NumColores);
	return ficha;
}

std::ostream& operator<< (std::ostream& out, const tFicha& ficha) {
	colorTexto(ficha.color);
	out << ficha.num + 1;
	colorTexto(blanco);
	return out;
}