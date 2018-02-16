#include "b.h"
#include <stdio.h>

b::b()
{

}

b::b(int nClaves)
{
	typedef b *pb;
	clavesUsadas = 0;
	clave = new nodo[nClaves];
	puntero = new pb[(nClaves + 1)];
	padre = NULL;
}


b::~b()
{
	delete[] clave;
	delete[] puntero;
}
