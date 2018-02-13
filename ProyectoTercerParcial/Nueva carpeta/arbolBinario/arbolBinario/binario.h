#pragma once
class binario
{
public:
	binario();
	binario *crearBinario(int x);
	~binario();
	void insertar(binario *&arbol, int x);
	void preOrden(binario *arbol);
	void enOrden(binario *arbol);
	void postOrden(binario *arbol);
	void verArbol(binario *arbol, int n);
private:
	int nro;
	binario *izq, *der;
};

