#include "BST.h"
#include<iostream>
using namespace std;

B_Node::B_Node(int val)
{
	value = val;
	hight = 1;
	right = left = NULL;
	circle.setScale(0, 0);
	r_arrow.setScale(0, 0);
	l_arrow.setScale(0, 0);
}

B_Node::B_Node(int val, Texture& CR , Texture& ARW , Font& FNT)
{
	value = val;
	hight=1;
	right = left=NULL;
	circle.setTexture(CR);
	l_arrow.setTexture(ARW);
	r_arrow.setTexture(ARW);
	num_text.setFont(FNT);
	circle.setScale(0, 0);
	r_arrow.setScale(0, 0.1);
	l_arrow.setScale(0, 0.1);
}

BST::BST()
{
	root = NULL;
	circle_texture.loadFromFile("normal.png");
	arrow_texture.loadFromFile("right-arrow.png");
	num_font.loadFromFile("Crasns.ttf");
}

B_Node* BST::balance(B_Node* rt)
{
	if (rt->balance_factor() > 1)
	{
		if (rt->left->balance_factor() == -1)
			rt->right = rotate_right(rt->right);

		rt = rotate_left(rt);
	}
	else if (rt->balance_factor() < -1)
	{
		if (rt->right->balance_factor() == 1)
			rt->left = rotate_left(rt->left);
		rt = rotate_left(rt);
	}
	return rt;
}




void B_Node::update_hight()
{
	int l = 0 , r = 0;
	if (left != NULL)
		l = left->hight;
	if (right != NULL)
		r = right->hight;

	hight = 1 + max(l, r);
}

void BST::update_pos(B_Node* rt,double prev_x,double prev_y)
{
	if (rt == NULL)
		return;

	rt->x = prev_x;
	rt->y = prev_y;
	update_pos(rt->right, prev_x + 1 / pow(2, prev_y + 1) , prev_y + 1);
	update_pos(rt->left, prev_x - 1 / pow(2, prev_y + 1), prev_y + 1);
}

int B_Node::balance_factor()
{
	int l =0 , r = 0;
	if (left != NULL)
		l = left->hight;
	if (right != NULL)
		r = right->hight;

	return l - r;
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
			
		rt= new B_Node(val,circle_texture,arrow_texture,num_font);	
		rt->num_text.setString(to_string(rt->value));
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
	rt = balance(rt);
	return rt;
}


void BST::draw(RenderWindow &window,B_Node* start)
{
	if (start == NULL)
		return;
	start->circle.setPosition(1366 * start->x, 780 * start->y / 7);
	start->num_text.setPosition(1366 * start->x, 780 * start->y / 7);
	

	window.draw(start->circle);
	window.draw(start->num_text);
	if (start->circle.getScale().x < 0.1)
		start->circle.setScale(start->circle.getScale().x + 0.001, start->circle.getScale().y+0.001);
	

	draw(window, start->left);
	draw(window, start->right);


}