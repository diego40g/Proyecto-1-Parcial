#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<allegro5/allegro.h> // Librería inicial de Allegro
#include<allegro5/allegro_primitives.h> // Addon de primitivas (figuras)
#include<allegro5/allegro_font.h>
#include<allegro5/allegro_ttf.h>
struct nodoBinario
{
	int nro;
	struct nodoBinario *izq, *der;
};
typedef struct nodoBinario *ABB;
class binario
{
public:
	binario();
	ABB crearNodo(int x);
	int getY();
	void valores(int x, int y);
	void insertar(ABB &arbol, int x);
	void preOrden(ABB arbol, ALLEGRO_FONT *font, FILE *);
	void enOrden(ABB arbol, ALLEGRO_FONT *font, FILE *);
	void postOrden(ABB arbol, ALLEGRO_FONT *font, FILE *);
	int verArbol(ABB arbol, int n, ALLEGRO_FONT *font, char* espacios, int **mat,FILE *,char*);

	
};

