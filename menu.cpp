#include <iostream>
#include <stdlib.h>

using namespace std; 

int main()
{
	int a, b; 
	cout << "1- VAMOS A JUGAR\n";
	cout << "2- CONTROLES\n";
	cout << "3- SALIR\n";
	cout << "La opcion deseada es: ";
	cin >> a; 
	do {
		switch (a)
		{
		case 1:
		case 2:
			
			break; 
		case 3:
			cout << "¿Seguro que desea salir?  SI o NO\n";
			cout << "1- SI\n";
			cout << "2- NO\n";
			cout << "La opcion elegida es: ";
			cin >> b;
			// REGRESO AL MENU PARA ELEGIR O SALIR DEL PROGRAMA
			if (b == 1)
			{
				return 0;
			}
			else
			{
				return main();
			}
			break;
		}
	} while (a != 3); //mientras sea distinto de 4 sigue 

	return 0;
}
