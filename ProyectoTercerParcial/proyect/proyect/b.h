#pragma once
struct nodo
{
	int valor;
	long registro;
};
class b
{
public:
	b();
	b(int nClaves);
	~b();
private:
	int clavesUsadas;
	nodo *clave;
	b **puntero;
	b *padre;

	friend class btree;
};

