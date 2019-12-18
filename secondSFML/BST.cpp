#include "BST.h"
using namespace std;
B_Node::B_Node(int val)
{
	value = val;
	hight = 1;
	right = left = NULL;
	circle.setScale(0.1, 0.1);
	r_arrow.setScale(0, 0.1);
	l_arrow.setScale(0, 0.1);
}

B_Node::B_Node(int val, Texture& CR , Texture& ARW)
{
	value = val;
	hight=1;
	right = left=NULL;
	circle.setTexture(CR);
	l_arrow.setTexture(ARW);
	r_arrow.setTexture(ARW);
	circle.setScale(0.1, 0.1);
	r_arrow.setScale(0, 0.1);
	l_arrow.setScale(0, 0.1);
}

BST::BST()
{
	root = NULL;
	circle_texture.loadFromFile("normal.png");
	arrow_texture.loadFromFile("right-arrow.png");
}

B_Node* BST::balance(B_Node* rt)
{
	if (rt->balance_factor() > 1)
	{
		if (rt->left->balance_factor() < -1)
			rt->right = rotate_right(rt->right);

		rt = rotate_left(rt);
	}
	else if (rt->balance_factor() < -1)
	{
		if (rt->right->balance_factor() > 1)
			rt->left = rotate_left(rt->left);
		rt = rotate_left(rt);
	}
	return rt;
}




void B_Node::update_hight()
{
	hight = 1 + max(left->hight , right->hight);
}

int B_Node::balance_factor()
{
	return left->hight - right->hight;
}





B_Node* BST::rotate_left(B_Node* parent)
{
	B_Node* y=parent->right;
	parent->right = y->left;
	y->left = parent;
	parent->update_hight();
	y->update_hight();
	return y;
}
B_Node* BST::rotate_right(B_Node* parent)
{
	B_Node* y = parent->left;
	parent->left = y->right;
	y->right = parent;
	parent->update_hight();
	y->update_hight();
	return y;

}

B_Node* BST::Insert(B_Node* rt, int val)
{
	if (rt == NULL)
	{
		rt= new B_Node(val,circle_texture,arrow_texture);
		
		return rt;
	}
	
	if (val < rt->value)
		rt->left = Insert(rt->left, val);
	else if (val > rt->value)
		rt->right = Insert(rt->right, val);
	else
		return rt;

	//AVL
	rt->update_hight();
	rt=balance(rt);
	
}