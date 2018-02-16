#define _CRT_SECURE_NO_WARNINGS
#include "binario.h"
#include<stdio.h>
#include<string.h>
#include<string>
#include<conio.h>
#include<Windows.h>

int VXb, VYb,cont;
binario::binario()
{
}
void binario::valores(int x, int y) {
	VXb = x;
	VYb = y;
}
void limpiarB(char *cad, int tam) {
	for (int i = 0; i<tam; i++) {
		*(cad + i) = '\0';
	}
}

void FOR(char *espacios, int n, int i)
{
	if (i == n)
	{
		return;
	}
	else
	{
		strcat(espacios, "   ");
		FOR(espacios, n, ++i);
	}
}
ABB binario::crearNodo(int x)
{
	ABB nuevoNodo = new(struct nodoBinario);
	nuevoNodo->nro = x;
	nuevoNodo->izq = NULL;
	nuevoNodo->der = NULL;

	return nuevoNodo;
}
void binario::insertar(ABB &arbol, int x)
{
	if (arbol == NULL)
	{
		arbol = crearNodo(x);
	}
	else if (x < arbol->nro)
		insertar(arbol->izq, x);
	else if (x > arbol->nro)
		insertar(arbol->der, x);
}
void binario::preOrden(ABB arbol, ALLEGRO_FONT *font, FILE *His)
{
	if (arbol != NULL)
	{
		VXb += 5;
		al_draw_textf(font, al_map_rgb_f(0, 0, 0), VXb, VYb, 0, "%d ", arbol->nro);
		fprintf(His, "%d", arbol->nro);
		VXb += 10;
		preOrden(arbol->izq, font,His);
		preOrden(arbol->der, font,His);
	}
}

void binario::enOrden(ABB arbol, ALLEGRO_FONT *font,FILE *His)
{
	if (arbol != NULL)
	{
		enOrden(arbol->izq, font,His);
		VXb += 5;
		al_draw_textf(font, al_map_rgb_f(0, 0, 0), VXb, VYb, 0, "%d ", arbol->nro);
		fprintf(His, "%d", arbol->nro);
		VXb += 10;
		enOrden(arbol->der, font,His);
	}
}

void binario::postOrden(ABB arbol, ALLEGRO_FONT *font,FILE *His)
{
	if (arbol != NULL)
	{
		postOrden(arbol->izq, font,His);
		postOrden(arbol->der, font,His);
		VXb += 5;
		al_draw_textf(font, al_map_rgb_f(0, 0, 0), VXb, VYb, 0, "%d ", arbol->nro);
		fprintf(His, "%d", arbol->nro);
		VXb += 10;
	}
}
int binario::verArbol(ABB arbol, int n, ALLEGRO_FONT *font, char* espacios, int **mat,FILE *His,char *QR)
{
	if (arbol == NULL) {
		al_flip_display(); // Dibujar en pantalla todo lo almacenado en el buffer, en este caso solamente está el círculo de arriba
		return cont;
	}
	else {
		char *aux=(char*)malloc(10*sizeof(char));
		*(*(mat + 0) + cont) = n * 9;
		printf("%d=%d->%d=%d//%d\t%d\n", *(*(mat + 0) + cont), n * 9, *(*(mat + 1) + cont), VYb, cont, arbol->nro);
		cont++;
		verArbol(arbol->der, n + 1, font, espacios, mat,His,QR);
		limpiarB(espacios, 100);
		FOR(espacios, n, 0);
		al_draw_circle((n * 9) + 10, VYb + 6, 10, al_map_rgb_f(1, 0, 0), 2);
		al_draw_textf(font, al_map_rgb_f(0, 0, 0), 0/*posicion en x*/, VYb/*posicion en y*/, 0, "%s  %d", espacios, arbol->nro);//es como printf																											   //coordenadas de Y no esta bien xD
		strcat(QR, "\n"); strcat(QR, espacios);
		int a = arbol->nro;
		_itoa(a,aux,10);
		//sprintf(aux, "%d", a);
		strcat(QR, aux);
		fprintf(His,"\n%s  %d", espacios, arbol->nro);
		*(*(mat + 1) + cont - 1) = VYb;
		VYb += 30;
		verArbol(arbol->izq, n + 1, font, espacios, mat,His,QR);
	}
}
int binario::getY() {
	return VYb;
}