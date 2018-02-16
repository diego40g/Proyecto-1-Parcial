#pragma once
#include"b.h"
#include<allegro5/allegro.h> // Librería inicial de Allegro
#include<allegro5/allegro_primitives.h> // Addon de primitivas (figuras)
#include<allegro5/allegro_font.h>
#include<allegro5/allegro_ttf.h>
#include<stdio.h>
#include<stdlib.h>
typedef b* pbnodo;
typedef nodo stclave;
class btree
{
public:
	btree(int nClv);
	~btree();
	void val(int,int);
	long Buscar(int clave);
	void verArbolB(char **graf, ALLEGRO_FONT *font, int tam,FILE*);
	bool Insertar(stclave clave);
	void Borrar(int clave);
	int Mostrar(char **gra);

private:
	stclave * lista;
	pbnodo *listapunt;
	void Inserta(stclave clave, pbnodo nodo, pbnodo hijo1, pbnodo hijo2);
	void BorrarClave(pbnodo nodo, int valor);
	void BorrarNodo(pbnodo nodo);
	void PasarClaveDerecha(pbnodo derecha, pbnodo padre, pbnodo nodo, int posClavePadre);
	void PasarClaveIzquierda(pbnodo izquierda, pbnodo padre, pbnodo nodo, int posClavePadre);
	void FundirNodo(pbnodo izquierda, pbnodo &padre, pbnodo derecha, int posClavePadre);
	int Ver(pbnodo nodo, char **gra, int cont);
	int nClaves, nodosMinimos;
	pbnodo Entrada;
};

