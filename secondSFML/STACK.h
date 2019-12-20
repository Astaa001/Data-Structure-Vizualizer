#include<SFML/Graphics.hpp>
#include<iostream>
#include<stack>
#include "Node.h"
#include "MainMenu.h"
using namespace sf;
using namespace std;
class STACK
{
private:
	bool poping;
	Node* head;
	Node* tail;
	int count;
	int position;
	double speed;
	Texture node_texture_0;
	Texture node_texture_1;
	Font num_font;
public:
	STACK();
	void push(int val);
	void push_draw(RenderWindow&);
	void pop();
	void pop_draw(RenderWindow&);
	int position_last_node();
	void Show();
};

