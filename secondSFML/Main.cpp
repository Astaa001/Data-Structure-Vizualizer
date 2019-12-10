#include<SFML/Graphics.hpp>
#include<iostream>
#include"linked_list.h"
#include<iostream>
#include<SFML/Graphics.hpp>

using namespace std;
using namespace sf;
int main()
{
	LinkedList l;
	RenderWindow window(VideoMode(1366, 780), "Visualizer");
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Key::Escape) )
				window.close();
			else if (Keyboard::isKeyPressed(Keyboard::Key::Enter))
			{
				l.push(3);
			}
			else if (Keyboard::isKeyPressed(Keyboard::Key::I) )
			{
				l.insert_at(5,1);
			}
			else if (Keyboard::isKeyPressed(Keyboard::Key::D) )
			{
				l.delete_at(0);
			}
			else if (Keyboard::isKeyPressed(Keyboard::Key::S))
			{
				l.find(1);
			}
		}
		window.clear();
		l.draw_N_move(window);
		window.display();
	}
}

