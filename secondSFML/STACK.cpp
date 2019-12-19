#include<SFML/Graphics.hpp>
#include<iostream>
#include "STACK.h"

STACK::STACK()
{
	poping = 0;
	head = tail = NULL;
	count = 0;
	position = 560;
	node_texture_0.loadFromFile("rounded-rectangle-orange.png");
	node_texture_1.loadFromFile("rounded-rectangle-green.png");
}
void STACK::push_draw(RenderWindow& window)
{
	Node* temp = tail;
	while (temp!=nullptr)
	{
		window.draw(temp->rectangle);
		temp = temp->next;
	}
	temp = tail;
	if (temp != NULL && temp->rectangle.getPosition().y > position_last_node())
	{
		temp->rectangle.move(0, -0.2);
	}
	else if(temp != NULL)
	{
		temp->rectangle.setTexture(node_texture_1);
	}
}
void STACK::push(int val)
{

	Node* node = new Node(val);
	if (head == NULL)
	{
		head = tail = node;
		position -= 90;
	}
	else
	{
		node->next = tail;
		tail = node;
		position -= 90;
	}

	tail->rectangle.setPosition(800,position+90);
	tail->rectangle.setTexture(node_texture_0);
	count++;

}

void STACK::pop()
{
	if (tail!=nullptr)
	{
		poping = 1;
		count--;
		position += 90;
	}
	else
	{
		cout << "mathzrsh ya zareef" << endl;
	}
}
void STACK::pop_draw(RenderWindow & window)
{
	if (poping)
	{
		tail->rectangle.setTexture(node_texture_0);
		if (tail->rectangle.getPosition().y < position_last_node())
		{
			tail->rectangle.move(0, 0.2);
		}
		else
		{
			Node* del = tail;
			tail = del->next;
			delete del;
			poping = 0;
		}
	}
}
int STACK::position_last_node()
{
	return position;
}
void STACK::Show() {
	STACK stack; 
	Clock clock;
	RenderWindow StackWindow(VideoMode(1024, 600), "StackWindow");
	Sprite background;
	Texture background_texture;
	background_texture.loadFromFile("StackBackground.jpg");
	background.setTexture(background_texture);
	Mouse cursor;
	while (StackWindow.isOpen())
	{
		Event event;
		while (StackWindow.pollEvent(event))
		{
			if (event.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Key::Home)) {
				StackWindow.close();
				MainMenu Menu;
				Menu.Show();
			}
			else if (Keyboard::isKeyPressed(Keyboard::Key::Enter) && clock.getElapsedTime().asMilliseconds() > 1200)
			{

				stack.push(5);
				clock.restart();
			}
			else if (Keyboard::isKeyPressed(Keyboard::Key::Space) && clock.getElapsedTime().asMilliseconds() > 1200)
			{
				stack.pop();
				clock.restart();
			}
			else if (Mouse::isButtonPressed(Mouse::Left)) {
				cout << cursor.getPosition(StackWindow).x << " " << cursor.getPosition(StackWindow).y << endl;
			}
		}

		StackWindow.clear();
		StackWindow.draw(background);
		stack.pop_draw(StackWindow);
		stack.push_draw(StackWindow);
		StackWindow.display();
	}
}