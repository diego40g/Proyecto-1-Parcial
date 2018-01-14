#include<stdio.h>
#include<conio.h>
#include<iostream> 

using namespace std;
#pragma once
class anidadas
{
public:
	class programa1
	{
	private:
		double num1;
		double num2;

	public:
		void impresion();
		void ingreso();

		void setnum1(double);
		void setnum2(double);
		double getnum1();
		double getnum2();
	};
	class programa2
	{
	private:
		double num3;
		double num4;

	public:
		void impresion2();
		void ingreso2();

		void setnum3(double);
		void setnum4(double);
		double getnum3();
		double getnum4();

	};
	class programa3
	{
	private:
		int num5;
		int num6;

	public:
		void ingreso3();
		void impresion3();

		void setnum5(int);
		void setnum6(int);
		int getnum5();
		int getnum6();
	};
	class programa4
	{
	private:
		int num7;
	public:
		void primos(int);
		void ingreso4();
		void impresion4();

		void setnum7(int);
		int getnum7();

	};
	class programa5
	{
	private:
		int num8;
	public:
		int factorial(int);
		void ingreso5();
		void impresion5();

		void setnum8(int);
		int getnum8();
	};
public:

	anidadas(void);
	~anidadas(void);
};


