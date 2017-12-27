/*
	UNIVERSIDAD DE LAS FUERZAS ARMADAS"ESPE"
	
Calcular SEN, COS Y TANG CON SERIE DE TAYLOR 

Autor: Diego Paz
Fecha de Creacion: 17-06-2017	Fecha de Modificacion:18-06-2017
Profesor: Ing. Edgar Fernando Solis Acosta
Carrera: Ingenieria en Sitemas e Informatica
*/
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
typedef struct taylor
{
	int n,x;
	float sin,cos,tan;
};

int factorial(int num);
void funtrigono(taylor);
char*num(char );
int main()
{
	taylor var;
	funtrigono(var);
	return 0;
}

char*num(char c)
{
	system("cls");
	printf("Ingrese el valor de %c: ",c);
	char *cad;
	int aux=0;
	cad=(char*)malloc(15*sizeof(char));
	gets(cad);

	for(int i=0;i<strlen(cad);i++)
	{
		if((*(cad+i)<=57)&&(*(cad+i)>=48))
		{
			aux++;
		}
	}
	if(aux!=strlen(cad))
	{
		return num(c);
	}
	else
	{
		return cad;
	}
}
void funtrigono(taylor var)
{
	char *car;
	float aux;
	int n;
	car=num('x');
	var.x=atoi(car);
	
	do{
	car=num('n');
	var.n=atoi(car);
	}while(var.n>10);
	
	n=var.x;
	if(var.x>360)
	do{
		var.x-=360;
	}while(var.x>360);
	
	//primer cuadrante
	if((var.x<=90)&&(var.x>=0))
	{
		var.sin=0;
		var.cos=0;
		aux=var.x*3.141592654/180;
		//sen(x)
		for(int i=0;i<var.n;i++)
		{
			var.sin+=(pow(-1,i)*(pow(aux,((2*i)+1)))/factorial(2*i+1));
		}
		//cos(x)
		for(int i=0;i<var.n;i++)
		{
			var.cos+=(pow(-1,i)*(pow(aux,(2*i)))/factorial(2*i));
		}
	}
		
	//segundo cuadrante
	if((var.x<=180)&&(var.x>=91))
	{
		var.sin=0;
		var.cos=0;
		aux=0;
		aux=var.x-90;
		aux=aux*3.141592654/180;
		//sen(x)
		for(int i=0;i<var.n;i++)
		{
			var.sin+=(pow(-1,i)*(pow(aux,(2*i)))/factorial(2*i));
		}
		//cos(x)
		for(int i=0;i<var.n;i++)
		{
			var.cos+=(pow(-1,i)*(pow(aux,((2*i)+1)))/factorial(2*i+1));
		}
		var.cos=-var.cos;
	}
			
	//tercer cuadrante
	if((var.x<=270)&&(var.x>=181))
	{
		var.sin=0;
		var.cos=0;
		aux=0;
		aux=var.x-180;
		aux=aux*3.141592654/180;
		//sen(x)
		for(int i=0;i<var.n;i++)
		{
			var.sin+=(pow(-1,i)*(pow(aux,((2*i)+1)))/factorial(2*i+1));
		}
		var.sin=-var.sin;
		//cos(x)
		for(int i=0;i<var.n;i++)
		{
			var.cos+=(pow(-1,i)*(pow(aux,(2*i)))/factorial(2*i));
		}
		var.cos=-var.cos;
	}
		
	//cuarto cuadrante
	if((var.x<=360)&&(var.x>=271))
	{
		var.sin=0;
		var.cos=0;
		aux=0;
		aux=var.x-270;
		aux=aux*3.141592654/180;
		//sen(x)
		for(int i=0;i<var.n;i++)
		{
			var.sin+=(pow(-1,i)*(pow(aux,(2*i)))/factorial(2*i));
		}
		var.sin=-var.sin;
		//cos(x)
		for(int i=0;i<var.n;i++)
		{
			var.cos+=(pow(-1,i)*(pow(aux,((2*i)+1)))/factorial(2*i+1));
		}
	}
		
	var.tan=(var.sin/var.cos);
	system ("cls");
	printf("\nEl valor de x es: %d\n",n);
	printf("\nEl valor de n es: %d\n",var.n);
	printf("\nEl valor del seno es igual a: %f\n",var.sin);
	printf("\nEl valor del coseno es igual a: %f\n",var.cos);	
	printf("\nEl valor de la tangente es igual a: %f\n",var.tan);
	return;
}

int factorial(int num)
{
	if(num==0)
	return num=1;
	else
	return(num*factorial(num-1));
}
