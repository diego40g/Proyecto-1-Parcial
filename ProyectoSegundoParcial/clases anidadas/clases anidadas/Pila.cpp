#include "Pila.h" 
#include <iostream>
using namespace std;

Pila::Pila()
{
	this->dato = "";
	this->num = 0;
	this->Nuevo = NULL;
	this->siguiente = NULL;
}

Pila *Pila::push(Pila *Nodo, string dato)
{
	Pila *temporal = new Pila();
	temporal->dato = dato;
	temporal->siguiente = Nodo;
	Nodo = temporal;
	return Nodo;
}

Pila *Pila::push(Pila *Nodo, float num)
{
	Pila *temporal = new Pila();
	temporal->num = num;
	temporal->siguiente = Nodo;
	Nodo = temporal;
	return Nodo;
}

Pila *Pila::pop(Pila *Nodo)
{
	if (Nodo != NULL)
	{
		Pila *temporal;
		temporal = Nodo;
		Nodo = Nodo->siguiente;
		temporal->dato = "";
		free(temporal);
	}
	else
	{
		printf("Lista Vacia");
		system("pause");
	}
	return Nodo;
}

void Pila::imprimirsig(Pila *Nodo)
{
	while (Nodo != NULL)
	{
		cout << Nodo->dato;
		Nodo = Nodo->siguiente;
	}
}

void Pila::imprimirnum(Pila *Nodo)
{
	while (Nodo != NULL)
	{
		printf("\n%.2f\n", Nodo->num);
		Nodo = Nodo->siguiente;
	}
}

float Pila::getnum(Pila *Nuevo)
{
	return Nuevo->num;
}

char Pila::getsig(Pila *Nuevo)
{
	char cad = Nuevo->dato[0];
	return cad;
}
