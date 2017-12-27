#include "listaSimple.h"
#include <stdio.h>
#include <stdlib.h>
bool listaSimple::llena()
{
	return (tope == MAX);
}

listaSimple::listaSimple()
{
	this->MAX = 100;
	this->tope = -1;
	this->cliente = 0;
	this->desCajero = 0;
	this->entreLlegas = 0;
	this->espera = 0;
	this->llegada = 0;
	this->salida = 0;
	this->servicio = 0;
	this->Nuevo = NULL;
	this->siguiente = NULL;
}

int listaSimple::getMAX()
{
	return MAX;
}

int listaSimple::gettope()
{
	return tope;
}

int listaSimple::getLlegada()
{
	return llegada;
}

int listaSimple::getSalida()
{
	return salida;
}

void listaSimple::settope(int tope)
{
	this->tope = tope;
}

void listaSimple::setMax(int MAX)
{
	this->MAX = MAX;
}

void listaSimple::setLlegada(int llegada)
{
	this->llegada = llegada;
}

listaSimple *listaSimple::push(listaSimple *Nodo, int cliente, int llegadaT, int esperaT, int descansoC_T, int servicioT, int salidaT, int entreLlegadasT)
{
	listaSimple *aux = new listaSimple();
	aux->cliente = cliente;
	aux->llegada = llegadaT;
	aux->espera = esperaT;
	aux->desCajero = descansoC_T;
	aux->servicio = servicioT;
	aux->salida = salidaT;
	aux->entreLlegas = entreLlegadasT;
	aux->siguiente = Nodo;
	Nodo = aux;
	//printf("\t%p\n", Nodo->siguiente);
	return Nodo;
}

void listaSimple::imprimirLista(listaSimple *nodito,int numUser)
{

	int cont=0;

	while (cont <= numUser) {
		if (cont == numUser)
		{
			if (nodito->getSalida() != 0)
			{
				printf("\n%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", nodito->cliente + 1,
					nodito->llegada,
					nodito->espera,
					nodito->desCajero,
					nodito->servicio,
					nodito->salida,
					nodito->entreLlegas);
			}
			return;
		//nodito = nodito->siguiente;
		}
		else
		{
			nodito = nodito->siguiente;
			cont++;
		}
	}
}

listaSimple *listaSimple::eliminar(listaSimple *Nodo)
{
	if (Nodo != NULL)
	{
		listaSimple *temporal;
		temporal = Nodo;
		Nodo = Nodo->siguiente;
		free(temporal);
	}
	else
	{
		printf("Lista Vacia");
		system("pause");
	}
	return Nodo;
}