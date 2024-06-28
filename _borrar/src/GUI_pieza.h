#pragma once

class GUI_pieza
{
	enum color { blanca, negra } color{};
	enum tipo { vacio, peon, torre, caballo, alfil, reina, rey } tipo{};

public:
	GUI_pieza();
	void dibuja_pieza();
};

