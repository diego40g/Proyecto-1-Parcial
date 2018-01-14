#include "anidadas.h"


anidadas::anidadas(void)
{
}


anidadas::~anidadas(void)
{
}


void anidadas::programa1::ingreso()
{
	double a, b;
	int f = 0;
	do
	{
		fflush(stdin);
		cout << "Ingrese el numero 1: ";
		f = scanf_s("%lf", &a);
	} while (f == 0);
	anidadas::programa1::setnum1(a);
	do
	{
		fflush(stdin);
		cout << "Ingrese el numero 2: ";
		f = scanf_s("%lf", &b);
	} while (f == 0);
	anidadas::programa1::setnum2(b);
	
}

void anidadas::programa1::impresion()
{
	cout << "El primer numero ingresado es :" << anidadas::programa1::getnum1() << endl;
	cout << "El segundo numero ingresado es :" << anidadas::programa1::getnum2() << endl;
	cout << "La suma de los numeros es:" << (num1 + num2) << endl;
	cout << "La resta de los numeros es:" << (num1 - num2) << endl;
}



void anidadas::programa1::setnum1(double a)
{
	num1 = a;
}
void anidadas::programa1::setnum2(double a)
{
	num2 = a;
}
double anidadas::programa1::getnum1()
{
	return num1;
}
double anidadas::programa1::getnum2()
{
	return num2;
}


void anidadas::programa2::ingreso2()
{
	double a, b;
	int f = 0;
	do
	{
		fflush(stdin);
		cout << "Ingrese el numero 1: ";
		f = scanf_s("%lf", &a);
	} while (f == 0);
	anidadas::programa2::setnum3(a);
	do
	{
		fflush(stdin);
		cout << "Ingrese el numero 2: ";
		f = scanf_s("%lf", &b);
	} while (f == 0);
	anidadas::programa2::setnum4(b);
}

void anidadas::programa2::impresion2()
{
	cout << "El primer numero ingresado es :" << anidadas::programa2::getnum3() << endl;
	cout << "El segundo numero ingresado es :" << anidadas::programa2::getnum4() << endl;
	cout << "La multiplicacion de los numeros es:" << (num3*num4) << endl;
	if (num4 == 0)cout << "No hay dision para cero" << endl;
	else
		cout << "La divison de los numeros es:" << (num3 / num4) << endl;
}

void anidadas::programa3::ingreso3()
{
	double a, b;
	int f = 0;
	do
	{
		fflush(stdin);
		cout << "Ingrese el numero 1: ";
		f = scanf_s("%lf", &a);
	} while (f == 0);
	anidadas::programa3::setnum5(a);	
	do
	{
		fflush(stdin);
		cout << "Ingrese el numero 2: ";
		f = scanf_s("%lf", &b);
	} while (f == 0);
	anidadas::programa3::setnum6(b);
	
}

void anidadas::programa3::impresion3()
{
	cout << "El primer numero ingresado es: " << anidadas::programa3::getnum5() << endl;
	cout << "El segundo numero ingresado es: " << anidadas::programa3::getnum6() << endl;
	cout << "El mod del primer numero y del segundo numero es: " << num5%num6 << endl;


}
void anidadas::programa4::ingreso4()
{
	double a;
	int f = 0;
	do
	{
		fflush(stdin);
		cout << "Ingrese el numero 1: ";
		f = scanf_s("%lf", &a);
	} while (f == 0);
	anidadas::programa4::setnum7(a);
}

void anidadas::programa4::primos(int num)
{
	int a;
	int cont = 1;
	cout << "Los numeros primos, hasta el numero  "<<num<<" son: "<< endl;
	for (int j = 1; j <= num; j++)
	{
		a = 0;
		for (int i = 1; i<(j + 1); i++) {
			if (j%i == 0) {
				a++;
			}
		}
		if (a != 2) {

		}
		else {
			cout << j << " ";
			if (0 == j % 10)
				cout << endl;
		}

		cont++;
	}

	cout << endl;
}

void anidadas::programa5::ingreso5()
{
	double a;
	int f = 0;
	do
	{
		fflush(stdin);
		cout << "Ingrese el numero 1: ";
		f = scanf_s("%lf", &a);
	} while (f == 0);
	anidadas::programa5::setnum8(a);
}
int anidadas::programa5::factorial(int numero)
{
	if (numero <= 1)
		return 1;
	else
		return numero * factorial(numero - 1);
}
void anidadas::programa5::impresion5()
{
	cout << "El numero ingresado es: " << anidadas::programa5::getnum8() << endl;
	cout << "El factorial es: " << anidadas::programa5::factorial(num8)<<endl;
	
}

void anidadas::programa4::impresion4()
{
	cout << "El numero ingresado es: " << anidadas::programa4::getnum7()<<endl;
	anidadas::programa4::primos(num7);
}

void anidadas::programa4::setnum7(int a)
{
	num7 = a;
}

void anidadas::programa5::setnum8(int a)
{
	num8 = a;
}
int anidadas::programa5::getnum8()
{
	return num8;
}
int anidadas::programa4::getnum7()
{
	return num7;
}

void anidadas::programa2::setnum3(double a)
{
	num3 = a;
}
void anidadas::programa2::setnum4(double a)
{
	num4 = a;
}

void anidadas::programa3::setnum5(int a)
{
	num5 = a;
}
void anidadas::programa3::setnum6(int a)
{
	num6 = a;
}

int anidadas::programa3::getnum5()
{
	return num5;
}
int anidadas::programa3::getnum6()
{
	return num6;
}


double anidadas::programa2::getnum3()
{
	return num3;
}
double anidadas::programa2::getnum4()
{
	return num4;
}
