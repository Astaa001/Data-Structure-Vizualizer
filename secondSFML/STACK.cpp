#include<SFML/Graphics.hpp>
#include<iostream>
#include "STACK.h"

STACK::STACK()
{
	poping = 0;
	head = tail = NULL;
	count = 0;
	position = 560;
	speed = 0.2;
	node_texture_0.loadFromFile("rounded-rectangle-orange.png");
	node_texture_1.loadFromFile("rounded-rectangle-green.png");
	num_font.loadFromFile("Crasns.ttf");
}
void STACK::push_draw(RenderWindow& window)
{
	Node* temp = tail;
	while (temp!=nullptr)
	{
		window.draw(temp->rectangle);
		window.draw(temp->num);
		temp = temp->next;
	}
	temp = tail;
	if (temp != NULL && temp->rectangle.getPosition().y > position_last_node())
	{
		temp->rectangle.move(0, -speed);
		temp->num.move(0, -speed);
	}
	else if(temp != NULL)
	{
		temp->rectangle.setTexture(node_texture_1);
	}
}
void STACK::push(int val)
{

	Node* node = new Node(val);
	node->num.setString(to_string(val));
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
	tail->num.setPosition(850, position + 130);
	tail->rectangle.setTexture(node_texture_0);
	tail->num.setFont(num_font);
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
			tail->rectangle.move(0, speed);
			tail->num.move(0, speed);
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
	bool ispressed = 0; Text UserText;
	UserText.setCharacterSize(30); UserText.setFillColor(Color::White);
	UserText.setFont(num_font); UserText.setStyle(Text::Underlined);
	UserText.setPosition(300, 57);
	// Push Button 
	Sprite push_btn;
	Texture push_btn_tex;
	push_btn_tex.loadFromFile("button.png");
	push_btn.setTexture(push_btn_tex);
	push_btn.setPosition(400, 50);
	push_btn.setScale(0.1, 0.1);
	// Pop Button
	Sprite pop_btn;
	Texture pop_btn_tex;
	pop_btn_tex.loadFromFile("button.png");
	pop_btn.setTexture(pop_btn_tex);
	pop_btn.setPosition(400, 100);
	pop_btn.setScale(0.1, 0.1);
	//InputTextbox saeed photoshop lel png
	Sprite Textbox; Texture Textbox_texture;
	Textbox_texture.loadFromFile("TextboxPic.png");
	Textbox.setTexture(Textbox_texture);
	Textbox.setPosition(250, 35);
	Textbox.setScale(0.15, 0.18);

	string UserInput; int FinalNumber=0;
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
			else if (ispressed)
			{
				if (event.type == Event::TextEntered) {
					if (event.text.unicode > 47 && event.text.unicode < 58) {
						UserInput += char(event.text.unicode);
						UserText.setString(UserInput);
					}
				}
				else if (Keyboard::isKeyPressed(Keyboard::BackSpace)) {
					if (!UserInput.empty()) {
						UserInput.erase(UserInput.size() - 1);
						UserText.setString(UserInput);
					}

				}
				else if (Keyboard::isKeyPressed(Keyboard::Enter) && clock.getElapsedTime().asMilliseconds() > 1200) {
					string curnum = UserText.getString();
					if (!curnum.empty()) {
						FinalNumber = stoi(curnum);
						stack.push(FinalNumber);
						UserInput = "";
						UserText.setString(UserInput);
						ispressed = 0;
						clock.restart();
					}
				}
			}
			// push
			else if ((cursor.getPosition(StackWindow).x >= 403 && cursor.getPosition(StackWindow).x <= 477 && cursor.getPosition(StackWindow).y >= 52 && cursor.getPosition(StackWindow).y <= 83 && Mouse::isButtonPressed(Mouse::Left))) {
				ispressed = 1;
			}
			// pop
			else if ((cursor.getPosition(StackWindow).x >= 403 && cursor.getPosition(StackWindow).x <= 477 && cursor.getPosition(StackWindow).y >= 103 && cursor.getPosition(StackWindow).y <= 133 && Mouse::isButtonPressed(Mouse::Left) && clock.getElapsedTime().asMilliseconds() > 1200))//&& clock.getElapsedTime().asMilliseconds() > 1200)) {
			{
				stack.pop();
				clock.restart();
			}
			
		}

		StackWindow.clear();
		StackWindow.draw(background);
		StackWindow.draw(Textbox);
		StackWindow.draw(UserText);
		StackWindow.draw(push_btn);
		StackWindow.draw(pop_btn);
		stack.pop_draw(StackWindow);
		stack.push_draw(StackWindow);
		StackWindow.display();
	}
}