#include <iostream>
#include "Isla.h"
using namespace std;

int main()
{
	char matriz[5][5];
	char* m = matriz[0];
	Isla i = Isla(5, m);
	i.generarIsla();
	i.mostrarIsla();
}