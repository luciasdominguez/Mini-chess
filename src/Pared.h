#pragma once
#include "Vector2D.h" 
class Pared
{
private:
	unsigned char rojo;
	unsigned char verde;
	unsigned char azul;

public:
	Vector2D limite1;
	Vector2D limite2;
	void setColor(unsigned char r, unsigned char g, unsigned char b);
	Pared();
	void dibuja();
};