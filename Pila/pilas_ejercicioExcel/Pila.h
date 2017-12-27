#ifndef Pila_H
#define Pila_H
#include <stdio.h>
class Pila
{
public:
	Pila();
	bool llena();
	void pushCliente(int elem);
	void pushtiempoespera(int elem);
	void pushtiempollegada(int elem);
	bool vacia();
	int pop();
private:
	int *pila;
	int tope;
	int MAX;
	int cliente;
	int tiempoLlegada;
	int tiempoEspera;
	int tiempoDescansoCajero;
	int tiempoServicio;
	int tiempoSalida;
	int tiempo_entreLlegadas;
};
#endif
