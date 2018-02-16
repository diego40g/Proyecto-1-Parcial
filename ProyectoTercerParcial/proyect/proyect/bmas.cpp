#include "bmas.h"
queue<pNode>q;
int nVal = 0;
int nPointer = 0;
node *Root = NULL;
int xbm = 0, ybm = 0;
bmas::bmas()
{
}
//-----------------------------------------------

//-----------------------------------------------

void bmas::valores(int pointer, int val) {
	nPointer = pointer;
	nVal = val;
}
void bmas::reiniciarBmas() {
	Root = NULL;
	xbm = 0;
	ybm = 0;
}
node* bmas::getTargetNode(node *tNode, int val) {
	if (tNode->leaf) return tNode;
	int i;
	for (i = 0; i<tNode->value.size(); i++) {
		if (tNode->value[i]>val) break;
	}
	return getTargetNode(tNode->child[i], val);
}
node* bmas::getNewNode(bool isLeaf, bool isRoot) {
	node* tmp = new node;
	tmp->isRoot = isRoot;
	tmp->leaf = isLeaf;
	tmp->last = NULL;
	return tmp;
}
void bmas::insertInParentNode(node *n, int kprime, node *nprime) {
	// printf("dbg: reached insertinparennode\n");
	//
	if (n->isRoot) {
		Root = getNewNode(false, true);
		n->isRoot = false;

		Root->child.push_back(n);
		Root->child.push_back(nprime);
		Root->value.push_back(kprime);
		n->par = Root;
		nprime->par = Root;
	}
	else {
		//printf("dbg: reached insertinparent node else\n");
		node *p = n->par;

		//printf("dbg: parent found\n");
		//printf("dbg: content of parent\n");
		//bfsTraverse(p);


		int i;
		for (i = 0; i<p->value.size(); i++) {
			if (p->value[i]>kprime) break;
		}
		int tmpK;
		node *tmpP;

		for (int j = i; j<p->value.size(); j++) {
			tmpK = p->value[j];
			tmpP = p->child[j + 1];

			p->value[j] = kprime;
			p->child[j + 1] = nprime;

			kprime = tmpK;
			nprime = tmpP;
		}
		p->value.push_back(kprime);
		p->child.push_back(nprime);
		nprime->par = p;

		//printf("dbg: reached before split\n");

		//printf("\n\np->child size: %d\n\n",p->child.size());

		if (p->child.size()>nPointer) {
			node *pprime = getNewNode(false, false);
			int nbytwoceil = (nPointer + 1) / 2;
			int kdoubleprime = p->value[nbytwoceil - 1];
			for (i = nbytwoceil; i<p->value.size(); i++) {
				pprime->child.push_back(p->child[i]);
				p->child[i]->par = pprime;
				pprime->value.push_back(p->value[i]);
			}
			pprime->child.push_back(p->child[i]);
			p->child[i]->par = pprime;


			p->value.erase(p->value.begin() + nbytwoceil - 1, p->value.end());
			p->child.erase(p->child.begin() + nbytwoceil, p->child.end());

			insertInParentNode(p, kdoubleprime, pprime);
		}
	}

}


void bmas::insertInLeafNode(node *leafNode, int k, node *p) {
	int i;
	for (i = 0; i<leafNode->value.size(); i++) {
		if (k<leafNode->value[i]) break;
	}
	int tmpK;
	node *tmpP;

	for (int j = i; j<leafNode->value.size(); j++) {
		tmpP = leafNode->child[j];
		tmpK = leafNode->value[j];

		leafNode->child[j] = p;
		leafNode->value[j] = k;

		p = tmpP;
		k = tmpK;
	}
	leafNode->child.push_back(p);
	leafNode->value.push_back(k);

}

void bmas::insert2(int k, node *p) {
	node *leafNode;
	if (Root == NULL) {
		Root = getNewNode(true, true);
		leafNode = Root;
	}
	else leafNode = getTargetNode(Root, k);

	//printf("dbg: target node content:\n");
	//if(leafNode->value.size()>0) bfsTraverse(leafNode);

	int keyValueCount = leafNode->value.size();
	if (keyValueCount<nVal) insertInLeafNode(leafNode, k, p);
	else {

		//printf("dbg: reached in else1\n");
		node* leafNode2 = getNewNode(true, false);
		insertInLeafNode(leafNode, k, p);

		//printf("dbg: inserted in leaf node\n");
		// printf("dbg: content\n");
		//bfsTraverse(leafNode);

		leafNode2->last = leafNode->last;
		leafNode2->par = leafNode->par;

		leafNode->last = leafNode2;

		int nbytwoceil;

		if (nPointer % 2 == 1)
		{
			nbytwoceil = (nPointer + 1) / 2;
			nbytwoceil -= 0.5;
		}
		else
		{
			nbytwoceil = (nPointer + 1) / 2;
		}

		for (int i = nbytwoceil; i<nPointer; i++)
		{
			leafNode2->child.push_back(leafNode->child[i]);
			leafNode2->value.push_back(leafNode->value[i]);
		}

		leafNode->value.erase(leafNode->value.begin() + nbytwoceil, leafNode->value.end());
		leafNode->child.erase(leafNode->child.begin() + nbytwoceil, leafNode->child.end());

		//printf("dbg: leafnode split complete\n");
		//printf("dbg: leafnode1 content:\n");
		// bfsTraverse(leafNode);
		//printf("dbg: leafnode2 content:\n");
		//bfsTraverse(leafNode2);

		int kprime = leafNode2->value[0];
		insertInParentNode(leafNode, kprime, leafNode2);
	}
}


void bmas::valueOfNodeInBox(node* tNode, ALLEGRO_FONT *font) {
	xbm += 10;
	printf(" [");
	al_draw_textf(font, al_map_rgb_f(0, 0, 0), xbm/*posicion en x*/, ybm/*posicion en y*/, 0, "[");//es como printf
	xbm += 3;
	int i;
	//int a = tNode->value.size();
	//printf("\nSIII\t%d",a );
	//system("pause");
	for (i = 0; i<tNode->value.size() - 1; i++) {
		printf("%d|", tNode->value[i]);
		al_draw_textf(font, al_map_rgb_f(0, 0, 0), xbm/*posicion en x*/, ybm/*posicion en y*/, 0, "%d|",tNode->value[i]);//es como printf
		xbm += 10;
	}
	if (tNode->value.size() > 0) { 
		printf("%d]", tNode->value[i]);
		al_draw_textf(font, al_map_rgb_f(0, 0, 0), xbm/*posicion en x*/, ybm/*posicion en y*/, 0, "%d]",tNode->value[i]);//es como printf
		xbm += 10;
	}
	//printf(" ");
}

void bmas::imp(ALLEGRO_FONT *font) {
	printf("\n\n\n");
	bfsTraverse(Root,font);
	//bfsTraverse(Root);
	printf("\n\n\n");
}



void bmas::bfsTraverse(node *tNode, ALLEGRO_FONT *font) {
	
	q.push(pNode(tNode, true));
	while (!q.empty()) {
		pNode p = q.front();
		//printf("  Got pNode ");
		node *temp = p.tNode;
		q.pop();
		valueOfNodeInBox(temp, font);
		//printf(" printed temp ");
		if (p.nl) { 
			printf("\n");
			ybm += 15;
			xbm = 0;
		}
		int i;
		if (!temp->leaf) {
			for (i = 0; i<temp->child.size() - 1; i++) {
				q.push(pNode(temp->child[i], false));
			}
			//printf(" inserted second last child  ");
			if (p.nl) q.push(pNode(temp->child[i], true));
			else q.push(pNode(temp->child[i], false));
			//printf(" inserted  last child  ");
		}

	}
	al_flip_display(); // Dibujar en pantalla todo lo almacenado en el buffer, en este caso solamente está el círculo de arriba

}