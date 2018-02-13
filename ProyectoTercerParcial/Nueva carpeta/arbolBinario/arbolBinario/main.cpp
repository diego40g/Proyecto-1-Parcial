#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include"binario.h"
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#include"b.h"
#include"btree.h"

#define TAMANO 8
#include"avl.h"

/*
BINARIOS
void ingresar(char *cad)
{
	int c, i = 0;
	while ((c = _getch()) != 13)
	{
		if ((c >= 48 && c <= 57) || (c == 44))
		{
			*(cad + i) = c;
			printf("%c", c);
			i++;
		}
		*(cad + i) = '\0';
	}
	return;
}

float *tok(char *cad, int *tam)
{
	char *ptr;
	int i = 0;
	float *res = (float*)malloc(500 * sizeof(float));
	char aux;
	strtok_s(cad, ",", &ptr);
	//printf("\n%s",ptr);
	*(res + i) = atof(cad);
	while (strcmp(cad,"") != 0)
	{
		i++;
		cad = ptr;
		strtok_s(cad, ",", &ptr);
		//printf("\n%s",ptr);
		*(res + i) = atof(cad);
	}
	*tam = i;
	return res;
}


int main()
{
	binario *arbol = NULL;   // creado Arbol

	char *cadena = (char*)malloc(500 * sizeof(char));  // numero de nodos del arbol
	int x, n, tam; // elemento a insertar en cada nodo

	printf("\n\t\t  ..[ ARBOL BINARIO DE BUSQUEDA ]..  \n\n");

	/* printf(" Numero de nodos del arbol:  ");
	scanf("%d",&n);
	*/
	/*printf(" Ingresar expresion y separe los numeros con \",\":  \n");
	ingresar(cadena);

	float *res = (float*)malloc(500 * sizeof(float));
	res = tok(cadena, &tam);

	printf("\n");
	for (int i = 0; i<tam; i++)
	{
		printf(" Numero del nodo %d = %.2f->", i + 1, *(res + i));
		x = *(res + i);
		arbol->insertar(arbol, x);
	}

	printf("\n Mostrando ABB \n\n");
	arbol->verArbol(arbol, 0);

	printf("\n Recorridos del ABB");

	printf("\n\n En orden   :  ");
	arbol->enOrden(arbol);
	printf("\n\n Pre Orden  :  ");
	arbol->preOrden(arbol);
	printf("\n\n Post Orden :  ");
	arbol->postOrden(arbol);

	printf("\n\n");

	system("pause");
	return 0;
}*/


/*
B---------------------------------------------------------------------------------------------------------------------------------------

void ingresarN(char *cad)
{
	int c, i = 0;
	while ((c = _getch()) != 13)
	{
		if ((c >= 48 && c <= 57))
		{
			*(cad + i) = c;
			printf("%c", c);
			i++;
		}
		*(cad + i) = '\0';
	}
	return;
}
void ingresar(char *cad)
{
	int c, i = 0;
	while ((c = _getch()) != 13)
	{
		if ((c >= 48 && c <= 57) || (c == 44))
		{
			*(cad + i) = c;
			printf("%c", c);
			i++;
		}
		*(cad + i) = '\0';
	}
	return;
}

/*int *tok(char *cad, int *tam)
{
	char *ptr;
	int i = 0;
	int *res = (int*)malloc(50 * sizeof(int));
	ptr = strtok(cad, ",");
	//printf("\n%s",ptr);
	*(res + i) = atof(ptr);
	while (ptr != NULL)
	{
		i++;
		ptr = strtok(NULL, ",");
		//printf("\n%s",ptr);
		*(res + i) = atof(ptr);
	}
	*tam = i;
	return res;
}*//*
int *tok(char *cad, int *tam)
{
	char *ptr;
	int i = 0;
	int *res = (int*)malloc(500 * sizeof(int));
	char aux;
	strtok_s(cad, ",", &ptr);
	//printf("\n%s",ptr);
	*(res + i) = atof(cad);
	while (strcmp(cad, "") != 0)
	{
		i++;
		cad = ptr;
		strtok_s(cad, ",", &ptr);
		//printf("\n%s",ptr);
		*(res + i) = atof(cad);
	}
	*tam = i;
	return res;
}
int main()
{
	char *m = (char*)malloc(5 * sizeof(char));
	char *cad = (char*)malloc(500 * sizeof(char));
	int orden, tam = 0;
	char **graf = (char**)malloc(50 * sizeof(char));
	for (int i = 0; i<10; i++)
	{
		fflush(stdin);
		*(graf + i) = (char*)malloc(10 * sizeof(char));
	}
	//for(int i=0;i<50)

	do {
		fflush(stdin);
		system("cls");
		printf("Ingrese el orden m= ");
		ingresarN(m);
		orden = atoi(m);
	} while ((orden <= 2) || (orden >= 101));

	printf("\n");

	printf(" Ingresar expresion y separe los numeros con \",\":  \n");
	ingresar(cad);
	int *res = (int*)malloc(50 * sizeof(int));
	res = tok(cad, &tam);

	btree arbol(orden - 1);
	stclave clave;
	int i;
	int *matriz = (int*)malloc(tam * sizeof(int));
	//   srand(time(NULL));
	for (i = 0; i < tam; i++) {
		do {
			matriz[i] = res[i];
			clave.valor = matriz[i];
			clave.registro = i;
			printf("%d->", matriz[i]);
		} while (!arbol.Insertar(clave));
	}

	char **g = (char**)malloc(50 * sizeof(char*));
	for (int i = 0; i<50; i++)
	{
		fflush(stdin);
		*(g + i) = (char*)malloc(10 * sizeof(char));
	}


	printf("mostrar: ");
	arbol.Mostrar(g);

	for (int i = 0; i<20; i++)
	{
		printf("\n\t%s", *(g + i));
	}
	printf("Buscar elemento 23: %d, posicion: ", matriz[23], arbol.Buscar(matriz[23]));
	system("PAUSE");

	for (i = 0; i < TAMANO; i++) {
		printf("Borrar: [%d] %d", i, matriz[i]);
		arbol.Borrar(matriz[i]);
		//      arbol.Mostrar();
	}
	arbol.Mostrar(g);
	return 0;
}
*/

/**************************************************************************************************************************************/

/*

AVL

int main()
{
	avl_node *root = NULL;
	int choice, item;
	avl avl;
	while (1)
	{
		printf("\n---------------------");
		printf("\nAVL Tree Implementation");
		printf("\n---------------------");
		printf("\n1.Insert Element into the tree");
		printf("\n2.Display Balanced AVL Tree");
		printf("\n3.InOrder traversal");
		printf("\n4.PreOrder traversal");
		printf("\n5.PostOrder traversal");
		printf("\n6.Exit");
		printf("\nEnter your Choice: ");
		scanf_s("%d",&choice);
		switch (choice)
		{
		case 1:
			printf("\nEnter value to be inserted: ");
			scanf_s("%d",&item);
			root = avl.insert(root, item);
			break;
		case 2:
			if (root == NULL)
			{
				printf("Tree is Empty");
				continue;
			}
			printf("Balanced AVL Tree:");
			avl.display(root, 1);
			break;
		case 3:
			printf("Inorder Traversal:");
			avl.inorder(root);
			printf("\n");
			break;
		case 4:
			printf("Preorder Traversal:");
			avl.preorder(root);
			printf("\n");
			break;
		case 5:
			printf("Postorder Traversal:");
			avl.postorder(root);
			printf("\n");
			break;
		case 6:
			exit(1);
			break;
		default:
			printf("Wrong Choice");
		}
	}
	return 0;
}
*/

