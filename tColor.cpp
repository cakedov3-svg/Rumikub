#include "tColor.h"
#include <iostream>
#include <string>

void colorTexto(tColor color) {
	switch (color) {
	case amarillo:
		std::cout << "\033[1;40;33m";
		break;
	case azul:
		std::cout << "\033[40;34m";
		break;
	case rojo:
		std::cout << "\033[40;31m";
		break;
	case verde:
		std::cout << "\033[40;32m";
		break;
	case blanco:
		std::cout << "\033[40;37m";
		break;

	}
}

std::string colorToStr(tColor color) {
	if (color == rojo) return "rojo";
	if (color == verde) return "verd";
	if (color == azul) return "azul";
	if (color == amarillo) return "amar";
}

int colorToInt(tColor color) {
	if (color == rojo) return 0;
	if (color == verde) return 1;
	if (color == azul) return 2;
	if (color == amarillo) return 3;
}