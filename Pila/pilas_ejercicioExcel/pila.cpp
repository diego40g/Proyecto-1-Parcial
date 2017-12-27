#include "pila.h"
#include <stdio.h>
#include <stdlib.h>

Pila::Pila()
{
	this->MAX = 100;
	this->tope = -1;
	this->pila=NULL;
	this->tiempoDescansoCajero = 0;
	this->tiempoEspera = 0;
	this->tiempoLlegada = 0;
	this->tiempoSalida = 0;
	this->tiempoServicio = 0;
	this->tiempo_entreLlegadas = 0;
}

bool Pila::llena()
{
	return (tope == MAX);
}

void Pila::pushCliente(int elem)
{
	if (this->llena());
		//ERROR
	else
	{
		tope++;
		pila[tope] = elem;
	}
}

void Pila::pushtiempoespera(int elem)
{
	if (this->llena());
	//ERROR
	else
	{
		tope++;
		pila[tope] = elem;
	}
}

void Pila::pushtiempollegada(int elem)
{
	if (this->llena());
	//ERROR
	else
	{
		tope++;
		pila[tope] = elem;
	}
}

bool Pila::vacia()
{
	return (tope == -1);
}

int Pila::pop()
{
	if (this->vacia());
	//ERROR
	else
	{
		int x = pila[tope];
		tope--;
		return x;
	}
}