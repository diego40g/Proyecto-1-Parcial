/*
UNIVERSIDAD DE LAS FUERZAS ARMADAS"ESPE"

ejercicio de pila implementacion del push y pop

imlementacion de atencion de un banco con:
-Cliente
-Tiempo de llegada
-Tiempo de espera
-Tiepo de descanso del Cajero
-Tiempo del Servicio
-Tiempo de Salida
-Tiempo entre llegadas

Autores: Michael Morales
Diego Paz

Fecha de Creacion: 15-12-2017	Fecha de Modificacion: 17-12-2017
Profesor: Ing. Edgar Fernando Solis Acosta
Carrera: Ingenieria en Sitemas e Informatica
*/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <conio.h>
#include <string.h>
#include "listaSimple.h"

void valSalida(char *salida)
{
	int  i = 0, c=0;
	while ((c = _getch() != 13))
	{
		if (((c <= 78) && (c >= 83)) || ((c <= 110) && (c >= 115)))
		{
			*(salida + i) = c;
			printf("%c", c);
			i++;
		}
		*(salida + i) = '\0';
	}
}

int main()
{
	listaSimple *user = new listaSimple();
	listaSimple *auxNodo = NULL;
	char ex = 'N',aux[10]="F";
	srand(time_t(NULL));
	int numUser = 0, llegada, espera, desCajero, servicio, salida, entreLlegada;
	do {
		llegada = 0; espera = 0; desCajero = 0; servicio = 0; salida = 0; entreLlegada = 0;
		if (numUser == 0)
		{
			llegada = rand() % 25;
			espera = 0;
			desCajero = 0;
			servicio = rand() % 16;
			salida = espera + servicio;
			entreLlegada = llegada;
			user=user[numUser].push(user,numUser, llegada, espera, desCajero, servicio, salida, entreLlegada);
			numUser++;
		}
		else
		{
			llegada = auxNodo->getLlegada();
			llegada += 1 + rand() % 25;
			if (auxNodo->getSalida()>llegada)
			{
				espera = auxNodo->getSalida()-llegada;
			}
			if(llegada > auxNodo->getSalida())
			{
				desCajero = llegada - auxNodo->getSalida();
			}	
			servicio = 1+rand() % 16;
			salida = llegada + espera + servicio;
			entreLlegada = llegada - auxNodo->getLlegada();
			user=user->push(user, numUser, llegada, espera, desCajero, servicio, salida, entreLlegada);
			numUser++;
		}
		auxNodo = user;
		printf("\nIngrese un s/n si un nuevo usuario acaba de ingresar\n");
		gets_s(aux);
		printf("NUMERO DE USUARIOS: %d\n",numUser);
	} while ((strcmp(aux,"S")==0)||(strcmp(aux,"s")==0));
	printf("Cliente\t\tTiempoLlegada\tTiempoEspera\tTiempoDescanso\tTiempoServicio\tTiempoSalida\tTiempoEntre");
	while (numUser >= 0) {
		auxNodo->imprimirLista(user, numUser);
		numUser--;
	}
	
	system("pause");
}