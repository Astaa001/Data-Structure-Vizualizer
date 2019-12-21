#include<SFML/Graphics.hpp>
#include<iostream>
#include"linked_list.h"
#include<iostream>
#include<SFML/Graphics.hpp>
#include "BST.h"
#include<random>
using namespace std;
using namespace sf;
int main()
{
	int x = 1;
	BST avl;
	Clock coco ;
	RenderWindow window(VideoMode(1366, 780), "Visualizer");
	while (window.isOpen())
	{

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Key::Escape) )
				window.close();
			if (Keyboard::isKeyPressed(Keyboard::Key::Space )&& coco.getElapsedTime().asMilliseconds()>=500 )
			{
				int x = rand() % 99;
//				cout << x << endl;
				avl.root = avl.Insert(avl.root,x);
				cout << "Root value is :" << avl.root->value << "        Root hight is : " << avl.root->hight << '\n';
				coco.restart();
				avl.new_node_pos_updated = 0;
			}
			if (Keyboard::isKeyPressed(Keyboard::Key::Enter) && coco.getElapsedTime().asMilliseconds() >= 500)
			{
				//avl.remove(97);
				avl.root=avl.remove(NULL, avl.root, 41);
				
				coco.restart();
			}


		}

		window.clear();
		avl.update_pos(avl.root, 0.5,1);
		avl.draw(window,avl.root);
		window.display();
	}
	return 0;
}

