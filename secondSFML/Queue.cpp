#include "Queue.h"
#include "MainMenu.h"
#include<iostream>
using namespace std;
using namespace sf;


Queue::Queue()
{
	front = rear = deleted = NULL;
	Size = 0;
	shifting_rate = 0,speed=1.2;
	isdrawed = 0;
	node_texture.loadFromFile("dry.png");
	num_font.loadFromFile("Crasns.ttf");
}
void Queue::Enqueue(int value) {
	if (!isdrawed && deleted==NULL) {
		Node* tmp = new Node(value);
		tmp->num.setString(to_string(value));
		Size++;
		if (front == NULL && rear == NULL) {
			front = rear = tmp;
		}
		else
		{
			rear->next = tmp;
			rear = tmp;
		}

		tmp->circle.setPosition(70, -100);
		tmp->num.setPosition(80, -97);

		tmp->circle.setTexture(node_texture);
		tmp->num.setFont(num_font);
		isdrawed = 1;
	}
}
void Queue::Dequeue() {
	
	if (deleted== NULL && !isdrawed) {
		if (front == NULL) {
			cout << "Queue is Empty \n";
			return;
		}
		deleted = front;
		Size--;
	}
}
void Queue::DrawQueue(RenderWindow& window) {
	
	if (rear != NULL && isdrawed ==1)
	{
		if (rear->circle.getPosition().y < 310)
		{
			rear->circle.move(0, speed);
			rear->num.move(0, speed);
		}
		
		else if ( rear->circle.getPosition().x <= (1210-((Size-1)*dist_between_nodes)))
		{
			rear->circle.move(speed, 0);
			rear->num.move(speed, 0);
		}
		else {
			isdrawed = 0;
		}
		
		
	}
	Node* temp = front;
	while (temp != NULL)
	{
		window.draw(temp->circle);
		window.draw(temp->num);
		temp = temp->next;
	}
}

void Queue::DrawDelete(RenderWindow& window) {
	// delete front & shift front to next front 
	if (deleted != NULL) {
		if (deleted->circle.getPosition().y < 800)
		{
			deleted->circle.move(0, speed);
			deleted->num.move(0, speed);
		}
		else if (shifting_rate < dist_between_nodes)
		{
			shifting_rate += speed;
			Node* temp = deleted->next;
			while (temp != NULL)
			{
				temp->circle.move(speed, 0);
				temp->num.move(speed, 0);
				temp = temp->next;
			}
			
		}
		else
		{
			if (front == rear) {
				front = rear = NULL;
			}
			else {
				front = front->next;
			}
			delete deleted; 
			deleted = NULL;
			shifting_rate = 0;
		}
	}
	
	// draw code
	Node* temp = front; // code run right with or without it ?!!
	while (temp != NULL)
	{
		window.draw(temp->circle);
		window.draw(temp->num);
		temp = temp->next;
	}
	
}
int Queue::Length() {
	return Size;
}
void Queue::Show() {
	Queue queue; 
	// Menu and background
	RenderWindow QueueWindow(VideoMode(1366, 768), "QueueWindow");
	Sprite background;
	Texture background_texture;
	background_texture.loadFromFile("QueueBackground-2.jpg");
	background.setTexture(background_texture);
	background.setScale(2.2, 2);

	bool ispressed = 0; Text UserText; 
	UserText.setCharacterSize(30); UserText.setFillColor(Color::White);
	UserText.setFont(num_font); UserText.setStyle(Text::Underlined);
	UserText.setPosition(660, 35);
	// Push Button 
	Sprite push_btn;
	Texture push_btn_tex;
	push_btn_tex.loadFromFile("button.png");
	push_btn.setTexture(push_btn_tex);
	push_btn.setPosition(750,50);
	push_btn.setScale(0.1,0.1);
	// Pop Button
	Sprite pop_btn;
	Texture pop_btn_tex;
	pop_btn_tex.loadFromFile("button.png");
	pop_btn.setTexture(pop_btn_tex);
	pop_btn.setPosition(750, 100);
	pop_btn.setScale(0.1, 0.1);
	//InputTextbox saeed photoshop lel png
	Sprite Textbox; Texture Textbox_texture;
	Textbox_texture.loadFromFile("TextboxPic.png");
	Textbox.setTexture(Textbox_texture);
	Textbox.setPosition(610, 15);
	Textbox.setScale(0.15, 0.18);

	string UserInput; int FinalNumber;
	Mouse cursor;
	
	while (QueueWindow.isOpen())
	{
		Event event;
		while (QueueWindow.pollEvent(event))
		{
			if (event.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Key::Home)) {
				QueueWindow.close();
				MainMenu Menu;
				Menu.Show();
			}


			else if (ispressed) {
				if (event.type == Event::TextEntered) {
					if (event.text.unicode > 47 && event.text.unicode < 58 ) {
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
				else if (Keyboard::isKeyPressed(Keyboard::Enter)) {
					string curnum = UserText.getString();
					if (!curnum.empty()) {
						FinalNumber = stoi(curnum);
						queue.Enqueue(FinalNumber);
						UserInput = "";
						UserText.setString(UserInput);
						ispressed = 0;
					}
				}

			}


			else if ((cursor.getPosition(QueueWindow).x >= 752 && cursor.getPosition(QueueWindow).x <= 827 && cursor.getPosition(QueueWindow).y >= 51 && cursor.getPosition(QueueWindow).y <= 84 && Mouse::isButtonPressed(Mouse::Left))) {
				ispressed = 1;
			
			}
			else if ((Keyboard::isKeyPressed(Keyboard::Key::Space)) || (cursor.getPosition(QueueWindow).x >= 752 && cursor.getPosition(QueueWindow).x <= 827 && cursor.getPosition(QueueWindow).y >= 102 && cursor.getPosition(QueueWindow).y <= 134 && Mouse::isButtonPressed(Mouse::Left)))
			{
				queue.Dequeue();
			}

			
		}
		QueueWindow.clear();
		QueueWindow.draw(background);
		QueueWindow.draw(Textbox);
		QueueWindow.draw(UserText);
		QueueWindow.draw(push_btn);
		QueueWindow.draw(pop_btn);
		queue.DrawQueue(QueueWindow);
		queue.DrawDelete(QueueWindow);
		QueueWindow.display();
	}
}

