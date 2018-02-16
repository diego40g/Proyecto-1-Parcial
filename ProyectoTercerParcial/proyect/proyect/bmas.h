#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <queue>
#include <iomanip>
#include<conio.h>
#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<string.h>
#include<string>
#include<time.h>
#include<iostream>

#include<allegro5/allegro.h> // Librería inicial de Allegro
#include<allegro5/allegro_primitives.h> // Addon de primitivas (figuras)
#include<allegro5/allegro_font.h>
#include<allegro5/allegro_ttf.h>

using namespace std;

/*int nVal=0;
int nPointer=0;*/
struct node {
	bool leaf;
	bool isRoot;
	node *par;
	vector<int>value;
	vector<node*>child;
	node *last;
};
struct pNode {
	node *tNode;
	bool nl;
	pNode(node *Node, bool b) {
		tNode = Node;
		nl = b;
	}
	pNode() {
	}
};
/*node *Root = NULL;
queue<pNode>q;*/
class bmas
{
public:
	bmas();
	void reiniciarBmas();
	void valores(int, int);
	node* getTargetNode(node *tNode, int val);
	node* getNewNode(bool isLeaf, bool isRoot);
	void insertInParentNode(node *n, int kprime, node *nprime);
	void insertInLeafNode(node *leafNode, int k, node *p);
	void insert2(int k, node *p);
	void valueOfNodeInBox(node* tNode, ALLEGRO_FONT *font);
	void bfsTraverse(node *tNode, ALLEGRO_FONT *font);
	void imp(ALLEGRO_FONT *font);
};

