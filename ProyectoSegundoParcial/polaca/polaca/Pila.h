#pragma once
#include <string.h>
#include <string>

using namespace std;
class Pila
{
public:
	Pila();
	Pila *push(Pila *Nodo, string dato);
	Pila *push(Pila *Nodo, float num);
	Pila *pop(Pila *Nodo);
	void imprimirsig(Pila *Nuevo);
	void imprimirnum(Pila *Nuevo);
	float getnum(Pila *Nuevo);
	char getsig(Pila *Nuevo);
private:
	Pila * siguiente;
	string dato;
	float num;
	Pila *Nuevo;
}; 