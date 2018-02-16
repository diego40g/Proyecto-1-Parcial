#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<string.h>
#include<string>
#include<conio.h>
#include<stdio.h>
#include<stdlib.h>
#include<allegro5/allegro.h> // Librería inicial de Allegro
#include<allegro5/allegro_primitives.h> // Addon de primitivas (figuras)
#include<allegro5/allegro_font.h>
#include<allegro5/allegro_ttf.h>

using namespace std;
struct avl_node
{
	int data;
	struct avl_node *left;
	struct avl_node *right;
};
//typedef avl_node *root;
class avl
{
public:
	int height(avl_node *);
	int diff(avl_node *);
	avl_node *rr_rotation(avl_node *);
	avl_node *ll_rotation(avl_node *);
	avl_node *lr_rotation(avl_node *);
	avl_node *rl_rotation(avl_node *);
	avl_node* balance(avl_node *);
	void reiniciar();
	avl_node* insertar(avl_node *, int);
	void dibujarArbol(avl_node *, int, ALLEGRO_FONT *,FILE *,char*);
	void inorder(avl_node *, FILE *);
	void preorder(avl_node *, FILE *);
	void postorder(avl_node *, FILE *);
	avl();
private:
	avl_node * root;
};

