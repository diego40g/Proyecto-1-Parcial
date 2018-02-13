#define _CRT_SECURE_NO_WARNINGS
#include "btree.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

btree::btree(int nClv) : nClaves(nClv)
{
	lista = new stclave[nClaves + 1];
	listapunt = new pbnodo[nClaves + 2];
	nodosMinimos = nClaves / 2; // ((nClaves+1)/2)-1;
	Entrada = NULL;
}

btree::~btree()
{
	delete[] lista;
	delete[] listapunt;
	// Destruir árbol, algoritmo recursivo:
	BorrarNodo(Entrada);
}

void btree::BorrarNodo(pbnodo nodo)
{
	int i;

	if (!nodo) return;
	for (i = 0; i <= nodo->clavesUsadas; i++) BorrarNodo(nodo->puntero[i]);
	delete nodo;
}

void btree::Mostrar(char **gra)
{
	for (int i = 0; i<20; i++)
	{
		strcpy(*(gra + i), "");
	}
	printf("arbol");;
	int cont = 0;
	Ver(Entrada, gra, cont);
	printf("-----");
	system("pause");
}

void btree::Ver(pbnodo nodo, char **gra, int cont)
{
	int i; char *cad = (char*)malloc(50 * sizeof(char));
	//cont++;
	if (!nodo)
	{
		return;
	}
	for (i = 0; i < nodo->clavesUsadas - 1; i++)
	{
		printf("%d-",nodo->clave[i].valor);
		strcpy(cad, "");
		sprintf(cad, "%d", nodo->clave[i].valor);
		strcat(cad, "-");
		strcat(*(gra + cont), cad);
	}
	if (nodo->clavesUsadas)
	{
		printf("%d [",nodo->clave[i].valor);
		strcpy(cad, "");
		sprintf(cad, "%d", nodo->clave[i].valor);
		strcat(*(gra + cont), cad);
	}
	if (nodo->padre)
	{
		cont++;
		printf("%d",(nodo->padre)->clave[0].valor);
		strcpy(cad, "");
		sprintf(cad, "%d", (nodo->padre)->clave[0].valor);
	}
	else
	{
		cont++;
		printf("*");
	}
	printf("]");
	cont++;
	for (i = 0; i <= nodo->clavesUsadas; i++)
	{
		cont++;
		Ver(nodo->puntero[i], gra, cont);
	}
}

long btree::Buscar(int clave)
{
	pbnodo nodo = Entrada;
	int i;

	while (nodo) {
		i = 0;
		while (i < nodo->clavesUsadas && (nodo->clave[i].valor < clave)) i++;
		if (nodo->clave[i].valor == clave) return nodo->clave[i].registro;
		else nodo = nodo->puntero[i];
	}
	return -1L;
}

bool btree::Insertar(stclave clave)
{
	pbnodo nodo, padre;
	int i;

	// Asegurarse de que la clave no está en el árbol
	padre = nodo = Entrada;
	while (nodo) {
		padre = nodo;
		i = 0;
		while (i < nodo->clavesUsadas && (nodo->clave[i].valor < clave.valor)) i++;
		if (nodo->clave[i].valor == clave.valor && i < nodo->clavesUsadas) return false;
		else nodo = nodo->puntero[i];
	}
	nodo = padre;
	Inserta(clave, nodo, NULL, NULL);
	return true;
}

void btree::Inserta(stclave clave, pbnodo nodo, pbnodo hijo1, pbnodo hijo2)
{
	pbnodo padre, nuevo;
	int i, j;
	bool salir = false;

	// Insertar nueva clave en nodo:
	do {
		if (!nodo)
		{
			nodo = new b(nClaves);
			nodo->clavesUsadas = 0;
			nodo->padre = NULL;
			Entrada = nodo;
		}
		padre = nodo->padre;
		if (nodo->clavesUsadas == nClaves) // overflow
		{
			// Nodo derecho
			nuevo = new b(nClaves);
			// Construye lista ordenada:
			i = 0;
			while (nodo->clave[i].valor < clave.valor && i < nClaves) {
				lista[i] = nodo->clave[i];
				listapunt[i] = nodo->puntero[i];
				i++;
			}
			lista[i] = clave;
			listapunt[i] = hijo1;
			listapunt[i + 1] = hijo2;
			while (i < nClaves) {
				lista[i + 1] = nodo->clave[i];
				listapunt[i + 2] = nodo->puntero[i + 1];
				i++;
			}
			// Dividir nodos:
			// Nodo izquierdo:
			nodo->clavesUsadas = nClaves / 2;
			for (j = 0; j < nodo->clavesUsadas; j++) {
				nodo->clave[j] = lista[j];
				nodo->puntero[j] = listapunt[j];
			}
			nodo->puntero[nodo->clavesUsadas] = listapunt[nodo->clavesUsadas];

			// Nodo derecho:
			nuevo->clavesUsadas = nClaves - nodo->clavesUsadas;
			for (j = 0; j < nuevo->clavesUsadas; j++) {
				nuevo->clave[j] = lista[j + (nClaves / 2) + 1];
				nuevo->puntero[j] = listapunt[j + (nClaves / 2) + 1];
			}
			nuevo->puntero[nuevo->clavesUsadas] = listapunt[nClaves + 1];

			for (j = 0; j <= nodo->clavesUsadas; j++)
				if (nodo->puntero[j]) (nodo->puntero[j])->padre = nodo;
			for (j = 0; j <= nuevo->clavesUsadas; j++)
				if (nuevo->puntero[j]) (nuevo->puntero[j])->padre = nuevo;

			clave = lista[nClaves / 2];
			hijo1 = nodo;
			hijo2 = nuevo;
			nodo = padre;
		}
		else
		{
			// Inserta nueva clave en su lugar:
			i = 0;
			if (nodo->clavesUsadas > 0) {
				while (nodo->clave[i].valor < clave.valor && i < nodo->clavesUsadas) i++;
				for (j = nodo->clavesUsadas; j > i; j--)
					nodo->clave[j] = nodo->clave[j - 1];
				for (j = nodo->clavesUsadas + 1; j > i; j--)
					nodo->puntero[j] = nodo->puntero[j - 1];
			}
			nodo->clavesUsadas++;
			nodo->clave[i] = clave;
			nodo->puntero[i] = hijo1;
			nodo->puntero[i + 1] = hijo2;
			if (hijo1) hijo1->padre = nodo;
			if (hijo2) hijo2->padre = nodo;
			salir = true;
		}
	} while (!salir);
}

void btree::Borrar(int valor)
{
	pbnodo nodo;
	bool encontrado = false;
	int i;

	// Busca el nodo que contiene la clave, si existe
	nodo = Entrada;
	while (nodo && !encontrado) {
		i = 0;
		while (i < nodo->clavesUsadas && (nodo->clave[i].valor < valor)) i++;
		if (nodo->clave[i].valor == valor && i < nodo->clavesUsadas) encontrado = true;
		else nodo = nodo->puntero[i];
	}
	if (encontrado) BorrarClave(nodo, valor);
}

void btree::BorrarClave(pbnodo nodo, int valor)
{
	pbnodo actual, derecha, izquierda, padre;
	int posClavePadre, pos, i;

	// Buscar posición dentro de lista de claves:
	pos = 0;
	while (nodo->clave[pos].valor < valor) pos++;

	// ¿Está la clave en un nodo hoja?
	if (nodo->puntero[0]) { // No, se trata de un nodo intermedio
							// Buscar actual del valor siguiente:
		actual = nodo->puntero[pos + 1];
		while (actual->puntero[0]) actual = actual->puntero[0];
		// Intercambiar con el valor siguiente:
		nodo->clave[pos] = actual->clave[0];
		// La posición de la clave a borrar en ahora la 0:
		pos = 0;
	}
	else actual = nodo;

	// Borrar clave
	for (i = pos; i < actual->clavesUsadas; i++)
		actual->clave[i] = actual->clave[i + 1];
	actual->clavesUsadas--;

	if (actual == Entrada && actual->clavesUsadas == 0) {
		delete actual;
		Entrada = NULL;
		return;
	}

	// ¿Es el número de claves mayor que el mínimo para el nodo?
	if (actual == Entrada || actual->clavesUsadas >= nodosMinimos) return;

	do {
		// El número de claves es menor que el mínimo:
		// Buscar nodos a derecha e izquierda:
		padre = actual->padre;
		for (posClavePadre = 0;
			padre->puntero[posClavePadre] != actual;
			posClavePadre++);
		if (posClavePadre > 0)
			izquierda = padre->puntero[posClavePadre - 1];
		else izquierda = NULL;
		if (posClavePadre < padre->clavesUsadas)
			derecha = padre->puntero[posClavePadre + 1];
		else derecha = NULL;

		// Intentar pasar una clave de un nodo cercano:
		if (derecha && derecha->clavesUsadas > nodosMinimos)
			PasarClaveDerecha(derecha, padre, actual, posClavePadre);
		else if (izquierda && izquierda->clavesUsadas > nodosMinimos)
			PasarClaveIzquierda(izquierda, padre, actual, posClavePadre - 1);
		// Si no fue posible, fundir con un nodo cercano y una clave de padre:
		else if (derecha) // Usar nodo derecho
			FundirNodo(actual, padre, derecha, posClavePadre);
		else             // Usar el nodo izquierdo
			FundirNodo(izquierda, padre, actual, posClavePadre - 1);
		// Vuelta a empezar:
		actual = padre;
	} while (actual && actual != Entrada && actual->clavesUsadas < nodosMinimos);
}

void btree::PasarClaveDerecha(pbnodo derecha, pbnodo padre, pbnodo nodo, int posClavePadre)
{
	int i;

	nodo->clave[nodo->clavesUsadas] = padre->clave[posClavePadre];
	nodo->clavesUsadas++;
	padre->clave[posClavePadre] = derecha->clave[0];
	nodo->puntero[nodo->clavesUsadas] = derecha->puntero[0];
	if (derecha->puntero[0]) derecha->puntero[0]->padre = nodo;
	for (i = 0; i < derecha->clavesUsadas; i++) derecha->clave[i] = derecha->clave[i + 1];
	for (i = 0; i <= derecha->clavesUsadas; i++) derecha->puntero[i] = derecha->puntero[i + 1];
	derecha->clavesUsadas--;
}

void btree::PasarClaveIzquierda(pbnodo izquierda, pbnodo padre, pbnodo nodo, int posClavePadre)
{
	int i;

	for (i = nodo->clavesUsadas; i > 0; i--) nodo->clave[i] = nodo->clave[i - 1];
	for (i = nodo->clavesUsadas + 1; i > 0; i--) nodo->puntero[i] = nodo->puntero[i - 1];
	nodo->clavesUsadas++;
	nodo->clave[0] = padre->clave[posClavePadre];
	padre->clave[posClavePadre] = izquierda->clave[izquierda->clavesUsadas - 1];
	nodo->puntero[0] = izquierda->puntero[izquierda->clavesUsadas];
	if (nodo->puntero[0]) nodo->puntero[0]->padre = nodo;
	izquierda->clavesUsadas--;
}

void btree::FundirNodo(pbnodo izquierda, pbnodo &padre, pbnodo derecha, int posClavePadre)
{
	int i;

	izquierda->clave[izquierda->clavesUsadas] = padre->clave[posClavePadre];
	padre->clavesUsadas--;
	for (i = posClavePadre; i < padre->clavesUsadas; i++) {
		padre->clave[i] = padre->clave[i + 1];
		padre->puntero[i + 1] = padre->puntero[i + 2];
	}
	izquierda->clavesUsadas++;
	for (i = 0; i < derecha->clavesUsadas; i++)
		izquierda->clave[izquierda->clavesUsadas + i] = derecha->clave[i];
	for (i = 0; i <= derecha->clavesUsadas; i++) {
		izquierda->puntero[izquierda->clavesUsadas + i] = derecha->puntero[i];
		if (derecha->puntero[i]) derecha->puntero[i]->padre = izquierda;
	}
	izquierda->clavesUsadas += derecha->clavesUsadas;
	if (padre == Entrada && padre->clavesUsadas == 0) { // Cambio de entrada
		Entrada = izquierda;
		Entrada->padre = NULL;
		delete padre;
		padre = NULL;
	}
	delete derecha;
}
