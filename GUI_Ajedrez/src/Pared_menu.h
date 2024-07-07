#pragma once
#include "vector2D.h" 
class Pared_menu
{
private:
	unsigned char rojo;
	unsigned char verde;
	unsigned char azul;

public:
	Vector2D_menu limite1;
	Vector2D_menu limite2;
	void setColor(unsigned char r, unsigned char g, unsigned char b);
	Pared_menu();
	void dibuja();
};