#include<SFML/Graphics.hpp>
#pragma once
using namespace sf;
class B_Node
{
public:
	int value , hight;
	double x,y;
	B_Node * right ,* left;
	Sprite circle, r_arrow, l_arrow;
	B_Node(int);
	B_Node(int, Texture&, Texture&, Font&);
	void update_hight();
	int balance_factor();
	Text num_text;
};


class BST
{
	Texture circle_texture, arrow_texture;
	Font num_font;

public:
	B_Node* root;
	BST();
	B_Node* balance(B_Node*);
	B_Node* Insert(B_Node* ,int);
	B_Node* rotate_left(B_Node *);
	B_Node* rotate_right(B_Node*);
	void update_pos(B_Node* , double ,double );
	void draw(RenderWindow&,B_Node*);
};

