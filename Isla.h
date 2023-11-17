#pragma once
class Isla
{
private:
	int dimension;
	char* matriz;
public:
	Isla(int d, char* m);
	//Isla();
	//~Isla();
	void generarIsla();
	void mostrarIsla();
};

