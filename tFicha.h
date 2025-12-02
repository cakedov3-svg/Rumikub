#ifndef TFICHA_H
#define TFICHA_H
#include <fstream>

#include "tColor.h"

const int NumBarajas = 2;


struct tFicha {
	tColor color;
	int num;
};

bool compColorMayor(tFicha const& fichai, tFicha const& fichad);
tFicha intToFicha(int k, int l);
std::ostream& operator<< (std::ostream& out, const tFicha& ficha);


#endif 