#pragma once
#include "VVector2D.h" 
class Pared
{
private:
	unsigned char rojo;
	unsigned char verde;
	unsigned char azul;

public:
	VVector2D limite1;
	VVector2D limite2;
	void setColor(unsigned char r, unsigned char g, unsigned char b);
	Pared();
	void dibuja();
};