#pragma once
#include"SFML/Graphics.hpp"
#include<iostream>
using namespace sf;
using namespace std;


class MainMenu
{

	int MAX_NUMBER_OF_ITEMS; 
	int SelectedItemIndex;
	float Height, Width;
	RenderWindow* MenuWindow;
	Font font; 
	Text menu[5];

	
public:
	MainMenu();
	void SetMenuStatus();
	void MoveUp();
	void MoveDown();
	int GetPressedItem();
	void DrawMenu();
	void Show();
};

