#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <conio.h>
#include <string.h>
using namespace std;

struct nodo
{
     int nro;
     struct nodo *izq, *der;
};

typedef struct nodo *ABB;
/* es un puntero de tipo nodo que hemos llamado ABB, que ulitizaremos
   para mayor facilidad de creacion de variables */

ABB crearNodo(int x)
{
     ABB nuevoNodo = new(struct nodo);
     nuevoNodo->nro = x;
     nuevoNodo->izq = NULL;
     nuevoNodo->der = NULL;

     return nuevoNodo;
}
void insertar(ABB &arbol, int x)
{
     if(arbol==NULL)
     {
           arbol = crearNodo(x);
     }
     else if(x < arbol->nro)
          insertar(arbol->izq, x);
     else if(x > arbol->nro)
          insertar(arbol->der, x);
}

void preOrden(ABB arbol)
{
     if(arbol!=NULL)
     {
          printf("%d ",arbol->nro);
          preOrden(arbol->izq);
          preOrden(arbol->der);
     }
}

void enOrden(ABB arbol)
{
     if(arbol!=NULL)
     {
          enOrden(arbol->izq);
          printf("%d ",arbol->nro);
          enOrden(arbol->der);
     }
}

void postOrden(ABB arbol)
{
     if(arbol!=NULL)
     {
          postOrden(arbol->izq);
          postOrden(arbol->der);
          printf("%d ",arbol->nro);
     }
}

void FOR(int i,int n)
{
	if(i<n)
	{
		printf("   ");
		return FOR(++i,n);
	}
	else
	{
		return;
	}
}

void verArbol(ABB arbol, int n)
{
     if(arbol==NULL)
          return;
     verArbol(arbol->der, n+1);
	
	 int i=0;
	
     FOR(i,n);

     printf("%d\n",arbol->nro);

     verArbol(arbol->izq, n+1);
}

void ingresar(char *cad)
{
	int c, i = 0;
	while ((c = getch()) != 13)
	{
		if ((c >= 48 && c <= 57) || (c == 44) )
		{
			*(cad + i) = c;
			printf("%c",c);
			i++;
		}
		*(cad + i) = '\0';
	}
	return;
}

float *tok(char *cad, int *tam)
{
    char *ptr;
    int i=0;
    float *res = (float*)malloc(500*sizeof(float));
    ptr = strtok(cad,",");
    //printf("\n%s",ptr);
    *(res+i)=atof(ptr);
    while(ptr!=NULL)
    {
        i++;
        ptr=strtok(NULL,",");
		//printf("\n%s",ptr);
        *(res+i)=atof(ptr);
    }
    *tam=i;
    return res;
}

int main()
{
    ABB arbol = NULL;   // creado Arbol

    char *cadena=(char*)malloc(500*sizeof(char));  // numero de nodos del arbol
    int x,n,tam; // elemento a insertar en cada nodo

    printf("\n\t\t  ..[ ARBOL BINARIO DE BUSQUEDA ]..  \n\n");

   /* printf(" Numero de nodos del arbol:  ");
    scanf("%d",&n);
    */
    printf(" Ingresar expresion y separe los numeros con \",\":  \n");
    ingresar(cadena);

    float *res=(float*)malloc(500*sizeof(float));
    res=tok(cadena,&tam);

    printf("\n");
    for(int i=0;i<tam;i++)
    {
        printf(" Numero del nodo %d = %.2f->",i+1,*(res+i));
        x=*(res+i);
        insertar(arbol, x);
    }

    printf("\n Mostrando ABB \n\n");
    verArbol(arbol, 0);

    printf("\n Recorridos del ABB");

    printf("\n\n En orden   :  ");
    enOrden(arbol);
    printf("\n\n Pre Orden  :  ");
    preOrden(arbol);
    printf("\n\n Post Orden :  ");
    postOrden(arbol);

    printf("\n\n");

    system("pause");
    return 0;
}


