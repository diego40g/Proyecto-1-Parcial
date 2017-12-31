#pragma once
#include <string.h>
#include <string>

using namespace std;
class Pila
{
public:
	Pila();
	Pila *push(Pila *Nodo, string dato);
	Pila *pop(Pila *Nodo);
	void imprimir (Pila *Nuevo);
private:
	Pila * siguiente;
	string dato;
	Pila *Nuevo;
};

