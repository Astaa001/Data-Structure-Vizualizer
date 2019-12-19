#include<SFML/Graphics.hpp>
#include<iostream>
#include"linked_list.h"
#include"Queue.h"
#include"STACK.h"
#include"MainMenu.h"
using namespace std;
using namespace sf;
int main()
{
	MainMenu Menu;
	Menu.Show();
	
	// test Code Use it When you Need it 
	/*sf::RenderWindow window(sf::VideoMode(1366, 768), "SFML works!");
	sf::CircleShape shape(20.f);
	shape.setFillColor(sf::Color::Green);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			else if (Keyboard::isKeyPressed(Keyboard::Key::Up))
			{
				shape.move(0, -10);
			}
			else if (Keyboard::isKeyPressed(Keyboard::Key::Down))
			{
				shape.move(0, 10);
			}
			else if (Keyboard::isKeyPressed(Keyboard::Key::Left))
			{
				shape.move(-10, 0);
			}
			else if (Keyboard::isKeyPressed(Keyboard::Key::Right))
			{
				shape.move(10, 0);
			}
			cout << shape.getPosition().x << " " << shape.getPosition().y << endl;
		}

		window.clear();
		window.draw(shape);
		window.display();
	}*/
}

