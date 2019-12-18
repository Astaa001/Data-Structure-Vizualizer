#include<SFML/Graphics.hpp>
#pragma once
using namespace sf;
class B_Node
{
public:
	int value , hight;
	B_Node * right ,* left;
	Sprite circle, r_arrow, l_arrow;
	B_Node(int);
	B_Node(int, Texture&, Texture&);
	void update_hight();
	int balance_factor();
};


class BST
{
	B_Node* root;
	Texture circle_texture, arrow_texture;

public:
	BST();
	B_Node* balance(B_Node*);
	B_Node* Insert(B_Node* ,int);
	B_Node* rotate_left(B_Node *);
	B_Node* rotate_right(B_Node*);


};

