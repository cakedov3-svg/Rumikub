#ifndef TCOLOR_H
#define TCOLOR_H
#include <string>

const int NumFichas = 8, NumColores = 4;

enum tColor { rojo, verde, azul, amarillo, blanco };

void colorTexto(tColor color);
std::string colorToStr(tColor color);
int colorToInt(tColor color);

#endif