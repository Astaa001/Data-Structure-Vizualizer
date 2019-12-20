#include "MainMenu.h"
#include"linked_list.h"
#include"Queue.h"
#include"STACK.h"
using namespace std;
using namespace sf;
MainMenu::MainMenu() {
	MenuWindow = new RenderWindow(VideoMode(1024, 680), "Visualisar");
	Width = (*MenuWindow).getSize().x, Height = (*MenuWindow).getSize().y;
	MAX_NUMBER_OF_ITEMS = 4;
	SelectedItemIndex = 0;
}
void MainMenu::SetMenuStatus() {

	if (!font.loadFromFile("Chocolate Bar Demo.otf"))
	{
		// handle error
		cout << "SHIIIIT" << endl;
	}
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
	{
		menu[i].setFont(font);
		if (i == 0) {
			menu[i].setFillColor(Color::Red);
			menu[i].setString("Linked List");
			menu[i].setPosition(Vector2f(Width / 2.5, Height / (MAX_NUMBER_OF_ITEMS + 1) * 2.35));
		}
		else if (i == 1) {
			menu[i].setFillColor(Color::White);
			menu[i].setString("Stack");
			menu[i].setPosition(Vector2f(Width / 2.5, Height / (MAX_NUMBER_OF_ITEMS + 1) * 3.1));

		}
		else if (i == 2)
		{
			menu[i].setFillColor(Color::White);
			menu[i].setString("Queue");
			menu[i].setPosition(Vector2f(Width / 2.4, Height / (MAX_NUMBER_OF_ITEMS + 1) * 3.75));
		}
		else {
			menu[3].setFillColor(Color::White);
			menu[3].setString("AVL");
			menu[3].setPosition(Vector2f(Width / 2.25, Height / (MAX_NUMBER_OF_ITEMS + 1) * 4.5));
		}

	}
}
void MainMenu::DrawMenu() {
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
	{
		(*MenuWindow).draw(menu[i]);

	}
}

void MainMenu::MoveUp() {
	if (SelectedItemIndex - 1 >= 0)
	{
		menu[SelectedItemIndex].setFillColor(Color::White);
		SelectedItemIndex--;
		menu[SelectedItemIndex].setFillColor(Color::Red);
	}
}
void MainMenu::MoveDown() {
	if (SelectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS)
	{
		menu[SelectedItemIndex].setFillColor(Color::White);
		SelectedItemIndex++;
		menu[SelectedItemIndex].setFillColor(Color::Red);
	}
}
int MainMenu::GetPressedItem() {
	return SelectedItemIndex;
}

void MainMenu::Show() {
	
	LinkedList list; Queue queue; STACK stack;
	SetMenuStatus();
	Texture backgroundwall;
	backgroundwall.loadFromFile("FantasyLand.png");
	Sprite Menuwall;
	Menuwall.setTexture(backgroundwall);
	//Menu choices Animations
	Sprite Choice, Choice2;
	Texture choice;
	if (!choice.loadFromFile("Untitled-1-Recovered.png"))
	{
		cout << "choice not found";
	}
	Choice.setTexture(choice);
	Choice.setPosition(0, 415);
	Choice.setScale(0.3, 0.27);

	Choice2.setTexture(choice);
	Choice2.setPosition(1024 - (0.3 * 1307), 315);
	Choice2.setScale(0.3, 0.27);
	//##############(Open Window)##############//
	while ((*MenuWindow).isOpen())
	{
		// Menu choices Animation
		if (Choice.getPosition().x < 310)
		{
			Choice.move(0.5, 0);
		}
		if (Choice2.getPosition().x > 310)
		{
			Choice2.move(-0.5, 0);
		}

		Event evnt;
		while ((*MenuWindow).pollEvent(evnt))
		{
			switch (evnt.type)
			{
			case sf::Event::KeyReleased:
				switch (evnt.key.code)
				{
				case sf::Keyboard::Up:
					MoveUp();
					break;

				case sf::Keyboard::Down:
					MoveDown();
					break;

				case sf::Keyboard::Return:
					switch (GetPressedItem())
					{
					case 0:
						(*MenuWindow).close();
						list.Show();
						break;
					case 1:
						(*MenuWindow).close();
						stack.Show();
						break;
					case 2:
						(*MenuWindow).close();
						queue.Show();
						break;
					case 3:
						(*MenuWindow).close();
						//AVL.Show();
						return;
						break;
					}

					break;
				}

				break;
			case Event::Closed:
				(*MenuWindow).close();
				return;
				break;
			}
		}


		(*MenuWindow).clear();
		(*MenuWindow).draw(Menuwall);
		(*MenuWindow).draw(Choice);
		(*MenuWindow).draw(Choice2);
		DrawMenu();
		(*MenuWindow).display();

	}
}
