#include "binario.h"
#include <stdio.h>

binario::binario()
{
}

binario::~binario()
{
}

binario *binario::crearBinario(int x)
{
	binario *nuevoNodo = new binario();
	nuevoNodo->nro = x;
	nuevoNodo->izq = NULL;
	nuevoNodo->der = NULL;

	return nuevoNodo;
}

void binario::insertar(binario *&arbol, int x)
{
	if (arbol == NULL)
	{
		arbol = crearBinario(x);
	}
	else
	{
		if (x < arbol->nro)
		{
			insertar(arbol->izq, x);
		}
		else
		{
			if (x > arbol->nro)
			{
				insertar(arbol->der, x);
			}
		}
	}
}

void binario::preOrden(binario *arbol)
{
	if (arbol != NULL)
	{
		printf("%d ", arbol->nro);
		preOrden(arbol->izq);
		preOrden(arbol->der);
	}
}

void binario::enOrden(binario *arbol)
{
	if (arbol != NULL)
	{
		enOrden(arbol->izq);
		printf("%d ", arbol->nro);
		enOrden(arbol->der);
	}
}

void binario::postOrden(binario *arbol)
{
	if (arbol != NULL)
	{
		postOrden(arbol->izq);
		postOrden(arbol->der);
		printf("%d ", arbol->nro);
	}
}

void FOR(int i, int n)
{
	if (i < n)
	{
		printf("   ");
		return FOR(++i, n);
	}
	else
	{
		return;
	}
}

void binario::verArbol(binario *arbol, int n)
{
	if (arbol == NULL)
	{
		return;
	}
	verArbol(arbol->der, n + 1);
	int i = 0;
	FOR(i, n);
	printf("%d\n", arbol->nro);
	verArbol(arbol->izq, n + 1);
}