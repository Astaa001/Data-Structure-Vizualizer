#include<SFML/Graphics.hpp>
#pragma once
using namespace sf;
class B_Node
{
public:
	int value, hight;
	double x, y;
	B_Node* right, * left;
	Sprite circle;
	B_Node(int);
	B_Node(int, Texture& , Font&);
	void update_hight();
	int balance_factor();
	Text num_text;
	RectangleShape line_right, line_left;
	/*bool has_right_child;
	bool has_left_child;*/
};


class BST
{
	Texture circle_texture;
	Font num_font;
	B_Node* deleted;
	RectangleShape drawArrow(float x1, float y1, float x2, float y2);
public:
	bool new_node_pos_updated;
	B_Node* root;
	BST();
	Clock timer;
/*	B_Node* findNode(int val);
	B_Node* findParent(int val);
	B_Node* findMin(B_Node* start);
	void remove(int val);*/
	B_Node* remove(B_Node*,B_Node*,int val);
	B_Node* balance(B_Node*);
	B_Node* Insert(B_Node*, int);
	B_Node* rotate_left(B_Node*);
	B_Node* rotate_right(B_Node*);
	void update_pos(B_Node*, double, double);
	void draw(RenderWindow&, B_Node*);

};

