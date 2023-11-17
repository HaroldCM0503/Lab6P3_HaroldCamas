#pragma once
class Isla
{
private:
	int dimension;
	char* matriz;
public:
	Isla(int d, char* m);
	Isla();
	~Isla();

	int getDimension();
	char* getMatriz();

	void generarIsla();
	void mostrarIsla();
};

