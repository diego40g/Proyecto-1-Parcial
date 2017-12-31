#include "Pila.h" 
#include <iostream>
using namespace std;

Pila::Pila()
{
	this->dato = "";
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

void Pila::imprimir(Pila *Nodo)
{
	while (Nodo != NULL)
	{
		cout << Nodo->dato;
		Nodo = Nodo->siguiente;
	}
}
