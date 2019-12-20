#include<SFML/Graphics.hpp>
#include<iostream>
#include<string>
#include"Node.h"
#include "MainMenu.h"
using namespace sf;
using namespace std;

class LinkedList
{
private:
	const int dist_between_nodes = 100;
	Node* head;
	Node* tail;
	Node* inserted;
	Node* deleted;
	Node* appended;
	Node* checked;
	int found;
	int Size;
	double shifting_rate,speed;
	Texture normal_node, red_node, yellow_node, green_node, arrow_texture;
	Font num_font;
	Clock timer;
	const double PI = 3.14159265359;

public:
	LinkedList();
	void push(int val);
	void insert_at(int, int);
	void delete_at(int pos);
	void find(int);
	void draw_N_move(RenderWindow&);
	int length();
	void push_annimation();
	void insert_annimation();
	void delete_annimation();
	void find_annimation();
	void Show();

};