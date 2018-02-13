#pragma once
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
	avl_node* insert(avl_node *, int);
	void display(avl_node *, int);
	void inorder(avl_node *);
	void preorder(avl_node *);
	void postorder(avl_node *);
	avl();
private:
	avl_node * root;
};

