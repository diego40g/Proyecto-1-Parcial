#ifndef listaSimple_H
#define listaSimple_H
#include <stdio.h>
class listaSimple
{
public:
	listaSimple();
	int getLlegada();
	int getMAX();
	int gettope();
	int getSalida();
	void setMax(int MAX);
	void settope(int tope);
	void setLlegada(int llegada);
	listaSimple *push(listaSimple *Nodo, int cliente,int llegadaT, int esperaT, int descansoC_T, int servicioT, int salidaT, int entreLlegadas);
	void imprimirLista(listaSimple *Nuevo, int numUser);
	listaSimple *eliminar(listaSimple *Nodo);
	bool llena();

private:
	int cliente;
	int llegada;
	int espera;
	int desCajero;
	int servicio;
	int salida;
	int entreLlegas;
	listaSimple *siguiente;
	listaSimple *Nuevo = NULL;
	int MAX;
	int tope;
};
#endif

