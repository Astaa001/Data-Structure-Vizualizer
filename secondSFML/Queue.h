#include<SFML/Graphics.hpp>
#include<iostream>
#include<string>
#include"Node.h"
using namespace sf;
using namespace std;
class Queue{
private:
	Node* front, * rear,*deleted;
	int Size;
	double shifting_rate,speed;
	const int dist_between_nodes = 100;
	Texture node_texture;
	Font num_font;
	bool isdrawed;
public:
	Queue();
	void Enqueue(int);
	void Dequeue();
	void DrawQueue(RenderWindow&);
	void DrawDelete(RenderWindow&);
	int Length();
	void Show();

};