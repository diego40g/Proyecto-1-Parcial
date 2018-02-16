#pragma once
#include"b.h"
typedef b* pbnodo;
typedef nodo stclave;
class btree
{
public:
	btree(int nClv);
	~btree();
	long Buscar(int clave);
	bool Insertar(stclave clave);
	void Borrar(int clave);
	void Mostrar(char **gra);

private:
	stclave * lista;
	pbnodo *listapunt;
	void Inserta(stclave clave, pbnodo nodo, pbnodo hijo1, pbnodo hijo2);
	void BorrarClave(pbnodo nodo, int valor);
	void BorrarNodo(pbnodo nodo);
	void PasarClaveDerecha(pbnodo derecha, pbnodo padre, pbnodo nodo, int posClavePadre);
	void PasarClaveIzquierda(pbnodo izquierda, pbnodo padre, pbnodo nodo, int posClavePadre);
	void FundirNodo(pbnodo izquierda, pbnodo &padre, pbnodo derecha, int posClavePadre);
	void Ver(pbnodo nodo, char **gra, int cont);
	int nClaves, nodosMinimos;
	pbnodo Entrada;
};

