#pragma once
#include<SFML/Graphics.hpp>
#include<iostream>
#include<string>
using namespace sf;
using namespace std;
class Node
{
public:
	int value;
	Node* next;
	Sprite circle;
	Sprite arrow;
	Sprite rectangle;
	Text num;
	Node() {
		value = 0;
		next = NULL;
		circle.setScale(0.1, 0.1);
		arrow.setScale(0, 0.1);
		rectangle.setScale(0.25, 0.25);
	}
	Node(int val) {
		value = val;
		next = NULL;
		circle.setScale(0.1, 0.1);
		arrow.setScale(0, 0.1);
		rectangle.setScale(0.25, 0.25);
	}
};

