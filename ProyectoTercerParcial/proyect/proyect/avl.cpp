#include "avl.h"
#include <stdio.h>
#include<iostream>
#include<cstdio>
#include<sstream>
#include<algorithm>
#define pow2(n) (1 << (n))
int xavl = 0, yavl = 0;
char *espacios = (char*)malloc(200 * sizeof(char));
using namespace std;

avl::avl()
{
	root = NULL;
}
void avl::reiniciar() {
	xavl = 0;
	yavl = 0;
}
void limpiarAvl(char* cad, int tam) {
	for (int i = 0; i < tam; i++) {
		*(cad + i) = '\0';
	}
}

int avl::height(avl_node *temp)
{
	int h = 0;
	if (temp != NULL)
	{
		int l_height = height(temp->left);
		int r_height = height(temp->right);
		int max_height = max(l_height, r_height);
		h = max_height + 1;
	}
	return h;
}

/*
* Height Difference
*/
int avl::diff(avl_node *temp)
{
	int l_height = height(temp->left);
	int r_height = height(temp->right);
	int b_factor = l_height - r_height;
	return b_factor;
}

/*
* Right- Right Rotation
*/
avl_node *avl::rr_rotation(avl_node *parent)
{
	avl_node *temp;
	temp = parent->right;
	parent->right = temp->left;
	temp->left = parent;
	return temp;
}
/*
* Left- Left Rotation
*/
avl_node *avl::ll_rotation(avl_node *parent)
{
	avl_node *temp;
	temp = parent->left;
	parent->left = temp->right;
	temp->right = parent;
	return temp;
}

/*
* Left - Right Rotation
*/
avl_node *avl::lr_rotation(avl_node *parent)
{
	avl_node *temp;
	temp = parent->left;
	parent->left = rr_rotation(temp);
	return ll_rotation(parent);
}

/*
* Right- Left Rotation
*/
avl_node *avl::rl_rotation(avl_node *parent)
{
	avl_node *temp;
	temp = parent->right;
	parent->right = ll_rotation(temp);
	return rr_rotation(parent);
}

/*
* Balancing AVL Tree
*/
avl_node *avl::balance(avl_node *temp)
{
	int bal_factor = diff(temp);
	if (bal_factor > 1)
	{
		if (diff(temp->left) > 0)
			temp = ll_rotation(temp);
		else
			temp = lr_rotation(temp);
	}
	else if (bal_factor < -1)
	{
		if (diff(temp->right) > 0)
			temp = rl_rotation(temp);
		else
			temp = rr_rotation(temp);
	}
	return temp;
}

/*
* Insert Element into the tree
*/
avl_node *avl::insert(avl_node *root, int value)
{
	if (root == NULL)
	{
		root = new avl_node;
		root->data = value;
		root->left = NULL;
		root->right = NULL;
		return root;
	}
	else if (value < root->data)
	{
		root->left = insert(root->left, value);
		root = balance(root);
	}
	else if (value >= root->data)
	{
		root->right = insert(root->right, value);
		root = balance(root);
	}
	return root;
}

/*
* Display AVL Tree
*/
void FORavl(char *espacios, int n, int i)
{
	if (i == n)
	{
		return;
	}
	else
	{
		strcat(espacios, "   ");
		FORavl(espacios, n, ++i);
	}
}
void avl::display(avl_node *ptr, int level, ALLEGRO_FONT *font)
{
	int i;
	if (ptr != NULL)
	{
		display(ptr->right, level + 1, font);
		printf("\n");
		yavl += 15;
		if (ptr == root) {
			printf("Root -> ");
		}
		for (i = 0; i < level && ptr != root; i++){
			printf("        ");
		}
		limpiarAvl(espacios, 100);
		FORavl(espacios, level, 0);
		printf("%d", ptr->data);
		al_draw_circle((level * 9) + 10, yavl + 6, 10, al_map_rgb_f(1, 0, 0), 2);
		al_draw_textf(font, al_map_rgb_f(0, 0, 0), 0/*posicion en x*/, yavl/*posicion en y*/, 0, "%s  %d", espacios, ptr->data);//es como printf
		display(ptr->left, level + 1,font);
	}
}

/*
* Inorder Traversal of AVL Tree
*/
void avl::inorder(avl_node *tree)
{
	if (tree == NULL)
		return;
	inorder(tree->left);
	printf("%d  ", tree->data);
	inorder(tree->right);
}
/*
* Preorder Traversal of AVL Tree
*/
void avl::preorder(avl_node *tree)
{
	if (tree == NULL)
		return;
	printf("%d  ", tree->data);
	preorder(tree->left);
	preorder(tree->right);
}

/*
* Postorder Traversal of AVL Tree
*/
void avl::postorder(avl_node *tree)
{
	if (tree == NULL)
		return;
	postorder(tree->left);
	postorder(tree->right);
	printf("%d  ", tree->data);
}
