
#include "linked_list.h"
#include <cmath>

LinkedList::LinkedList()
{
	head = tail = inserted = deleted = appended = checked = NULL;
	Size = 0, shifting_rate = 0,speed=1.5;
	found = -1;
	normal_node.loadFromFile("normal.png");
	yellow_node.loadFromFile("yellow.png");
	green_node.loadFromFile("dry.png");
	red_node.loadFromFile("Red.png");
	arrow_texture.loadFromFile("right-arrow.png");
	num_font.loadFromFile("Crasns.ttf");
}

int LinkedList::length()
{
	return Size;
}
void LinkedList::push(int val)
{
	if (inserted == NULL && deleted == NULL && appended == NULL)
	{

		Size++;
		appended = new Node(val);
		appended->num.setString(to_string(val));
		if (head == NULL) // if empty
		{
			head = tail = appended;
		}
		else
		{
			tail->next = appended;
			tail->arrow.setTexture(arrow_texture);
			tail->arrow.setPosition(50 + (Size - 1) * dist_between_nodes, 310);
			tail = appended;
		}
		if (tail == head)
		{
			appended->circle.setPosition(70, 310);
			appended->num.setPosition(81, 317);
		}
		else
		{
			appended->circle.setPosition(1250, 310);
			appended->num.setPosition(1261, 317);
		}
		appended->circle.setTexture(normal_node);
		appended->num.setFont(num_font);
	}
}
void LinkedList::insert_at(int pos, int val)
{
	if (inserted == NULL && deleted == NULL && appended == NULL)
	{
		if (pos <= Size && pos >= 0)
		{
			Size++;
			Node* temp = head;
			inserted = new Node(val);
			inserted->num.setString(to_string(val));
			if (pos == 0)
			{
				inserted->next = head;
				head = inserted;
			}
			else
			{

				for (int i = 0; i < pos - 1; i++)
				{
					temp = temp->next;
				}
				inserted->next = temp->next;
				temp->next = inserted;
			}
			inserted->circle.setPosition((1 + pos) * dist_between_nodes, 10);
			inserted->arrow.setPosition(50 + inserted->circle.getPosition().x, inserted->circle.getPosition().y);
			inserted->num.setPosition((1 + pos) * dist_between_nodes+11, 14);
			inserted->circle.setTexture(normal_node);
			inserted->num.setFont(num_font);
		}
		else
			cout << "Cannot Insert In This Index\n";
	}
}

void LinkedList::delete_at(int pos)
{
	if (inserted == NULL && deleted == NULL && appended == NULL)
	{

		Node* temp = head;
		if (pos == 0)
		{
			deleted = head;
		}
		else
		{
			for (int i = 0; i < pos - 1; i++)
			{
				temp = temp->next;
			}
			deleted = temp->next;
			//temp->next = deleted->next;

		}
		Size--;
	}
}
void LinkedList::find(int target)
{
	if (inserted == NULL && deleted == NULL && appended == NULL && found == -1)
	{
		found = target;
		checked = head;
	}
}

void LinkedList::push_annimation()
{
	if (appended == head && appended->circle.getPosition().x < Size * dist_between_nodes)
	{
		appended->circle.move(speed, 0);
		appended->num.move(speed, 0);
	}
	else if (appended != head && appended->circle.getPosition().x > Size* dist_between_nodes)
	{
		appended->circle.move(-speed, 0);
		appended->num.move(-speed, 0);
	}
	else
		appended = NULL;

}

void LinkedList::insert_annimation()
{
	Node* temp = inserted->next;


	shifting_rate += speed;
	while (temp != NULL && shifting_rate < dist_between_nodes)
	{
		temp->circle.move(speed, 0);
		temp->num.move(speed, 0);
		temp->arrow.move(speed, 0);
		temp = temp->next;
	}
	if (inserted->circle.getPosition().y > 310)
	{
		inserted = NULL;
		shifting_rate = 0;
	}
	else if (shifting_rate >= dist_between_nodes)
	{
		inserted->circle.move(0, speed);
		inserted->num.move(0, speed);
		inserted->arrow.setTexture(arrow_texture);


		///////////////////EL4O8L BTA3 ROTATE ELARROW ELMAFROOD YEB2A HENA
		temp = head;

		// momken ne3melha PRE node

		while (temp->next != inserted && temp->next != NULL) temp = temp->next;
		double dist = pow(pow(dist_between_nodes, 2) + pow(310 - inserted->circle.getPosition().y, 2), 0.5);

		temp->arrow.setScale((dist - 50) / 512, 0.1);
		temp->arrow.setRotation(-180 * asin((310 - inserted->circle.getPosition().y) / dist) / PI);

		inserted->arrow.setPosition(inserted->circle.getPosition().x + 50, inserted->circle.getPosition().y);
		inserted->arrow.setScale((dist - 50) / 512, 0.1);
		inserted->arrow.setRotation(360 - (-180 * asin((310 - inserted->circle.getPosition().y) / dist) / PI));


	}
}

void LinkedList::delete_annimation()
{

	if (deleted->circle.getPosition().y > -85)
	{
		deleted->circle.move(0, -speed);
		deleted->num.move(0, -speed);
	}
	else if (shifting_rate < dist_between_nodes)
	{
		shifting_rate += speed;
		Node* temp = deleted->next;
		while (temp != NULL)
		{
			temp->circle.move(-speed, 0);
			temp->num.move(-speed, 0);
			temp->arrow.move(-speed, 0);
			temp = temp->next;
		}
	}
	else
	{
		shifting_rate = 0;
		if (deleted != head)
		{
			Node* temp = head;
			// 
			while (temp->next != deleted)
			{
				temp = temp->next;
			}
			if (deleted == tail) {
				tail = temp;
			} 
			temp->next = deleted->next;

		}
		else
			head = head->next;

		delete deleted;
		deleted = NULL;
	}
}
void LinkedList::find_annimation()
{

	//if Search Done
	if (found == -2)
	{
		if (timer.getElapsedTime().asSeconds() >= 1)
		{
			Node* temp = head;


			while (temp != NULL)
			{
				// Back To The Normal Node Color
				temp->circle.setTexture(normal_node);
				if (temp == checked)
					break;
				temp = temp->next;
			}
			found = -1;
			checked = NULL;
		}
	}

	else if (timer.getElapsedTime().asMilliseconds() > 400)
	{
		if (checked == NULL)
		{
			Node* temp = head;
			while (temp != NULL)
			{
				// NOT FOUNT ==== RED NODE
				temp->circle.setTexture(red_node);
				temp = temp->next;
			}
			found = -2;
		}

		else if (checked->value != found)
		{
			checked->circle.setTexture(yellow_node);
			checked = checked->next;
		}
		else
		{
			checked->circle.setTexture(green_node);
			found = -2;
		}

		timer.restart();

	}
}

void LinkedList::draw_N_move(RenderWindow& window)
{

	if (found != -1)
		find_annimation();

	if (inserted != NULL)
		insert_annimation();


	if (deleted != NULL)
		delete_annimation();


	if (appended != NULL)
		push_annimation();



	Node* temp = head;
	while (temp != NULL)
	{
		window.draw(temp->circle);
		window.draw(temp->num);
		if (temp != tail)
		{
			if (temp->arrow.getScale().x < 0.1 && appended == NULL)
				temp->arrow.setScale(temp->arrow.getScale().x + 0.001, 0.1);
			window.draw(temp->arrow);
		}


		temp = temp->next;
	}
}
void LinkedList::Show() {
	LinkedList list;
	RenderWindow Listwindow(VideoMode(1366, 768), "LinkedListWindow");
	Sprite background;
	Texture background_texture;
	background_texture.loadFromFile("QueueBackground-3.jpg");
	background.setTexture(background_texture);
	background.setScale(2.2, 2);
	// Text on Screen
	Text UserText,IdxText;
	UserText.setCharacterSize(30); UserText.setFillColor(Color::White);
	UserText.setFont(num_font); UserText.setStyle(Text::Underlined);
	UserText.setPosition(1110, 550);
	// Idx Text
	IdxText.setCharacterSize(30); IdxText.setFillColor(Color::White);
	IdxText.setFont(num_font); IdxText.setStyle(Text::Underlined);
	IdxText.setPosition(350, 550);
	string UserInput, UserInput_Idx; int FinalNumber = 0, FinalIdx = 0;
	// Append Button 
	Sprite Append_btn;
	Texture Append_tex;
	Append_tex.loadFromFile("button.png");
	Append_btn.setTexture(Append_tex);
	Append_btn.setPosition(1200, 500);
	Append_btn.setScale(0.1, 0.1);
	// find Button
	Sprite Find_btn;
	Texture Find_tex;
	Find_tex.loadFromFile("button.png");
	Find_btn.setTexture(Find_tex);
	Find_btn.setPosition(1200, 550);
	Find_btn.setScale(0.1, 0.1);
	//insert button
	Sprite insert_btn;
	Texture insert_tex;
	insert_tex.loadFromFile("button.png");
	insert_btn.setTexture(Find_tex);
	insert_btn.setPosition(450, 550);
	insert_btn.setScale(0.1, 0.1);
	//delete button
	Sprite delete_btn;
	Texture delete_tex;
	delete_tex.loadFromFile("button.png");
	delete_btn.setTexture(Find_tex);
	delete_btn.setPosition(1200, 600);
	delete_btn.setScale(0.1, 0.1);
	//InputTextbox saeed photoshop lel png
	Sprite Textbox, Posbox,Valuebox; Texture Textbox_texture;
	Textbox_texture.loadFromFile("TextboxPic.png");
	Textbox.setTexture(Textbox_texture);
	Textbox.setPosition(1050, 525);
	Textbox.setScale(0.15, 0.18);
	// First Textbox to value
	Valuebox.setTexture(Textbox_texture);
	Valuebox.setPosition(300, 525);
	Valuebox.setScale(0.15, 0.18);
	// Second textbox to idx
	Posbox.setTexture(Textbox_texture);
	Posbox.setPosition(150, 525);
	Posbox.setScale(0.15, 0.18);

	bool isAppended = 0, isFinded = 0, isInserted = 0, isDeleted = 0,ValueTyped=0;
	// mouse
	Mouse cursor;
	while (Listwindow.isOpen())
	{
		Event event;
		while (Listwindow.pollEvent(event))
		{
			if (event.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Key::Home)) {
				Listwindow.close();
				MainMenu Menu;
				Menu.Show();
			}

			else if (isAppended) {

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
				else if (Keyboard::isKeyPressed(Keyboard::Enter)) {
					string curnum = UserText.getString();
					if (!curnum.empty()) {
						FinalNumber = stoi(curnum);
						list.push(FinalNumber);
						UserInput = "";
						UserText.setString(UserInput);
					}
						isAppended = 0;
				}

			}
			else if (isFinded) {

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
				else if (Keyboard::isKeyPressed(Keyboard::Enter)) {
					string curnum = UserText.getString();
					if (!curnum.empty()) {
						FinalNumber = stoi(curnum);
						list.find(FinalNumber);
						UserInput = "";
						UserText.setString(UserInput);
					}
						isFinded = 0;
				}

			}
			else if (isDeleted) {
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
				else if (Keyboard::isKeyPressed(Keyboard::Enter)) {
					string curnum = UserText.getString();
					if (!curnum.empty()) {
						FinalNumber = stoi(curnum);
						list.delete_at(FinalNumber);
						UserInput = "";
						UserText.setString(UserInput);
					}
						isDeleted = 0;
				}

			}
			else if (isInserted) {
				if (!ValueTyped) {
					IdxText.setPosition(350, 550);
					if (event.type == Event::TextEntered) {
						if ((event.text.unicode > 47 && event.text.unicode < 58 )) {
							UserInput_Idx += char(event.text.unicode);
							IdxText.setString(UserInput_Idx);
						}
					}
					else if (Keyboard::isKeyPressed(Keyboard::BackSpace)) {
						if (!UserInput_Idx.empty()) {
							UserInput_Idx.erase(UserInput_Idx.size() - 1);
							IdxText.setString(UserInput_Idx);
						}

					}
					else if (Keyboard::isKeyPressed(Keyboard::Enter)) {
						string curnum = IdxText.getString();
						if (!curnum.empty()) {
							FinalNumber = stoi(curnum);
							// store the value

							UserInput_Idx = "";
							IdxText.setString(UserInput_Idx);
						}
							ValueTyped = 1;
					}
				}
				else if (ValueTyped) {
					IdxText.setPosition(200, 550);
					if (event.type == Event::TextEntered) {
						if (event.text.unicode > 47 && event.text.unicode < 58) {
							UserInput_Idx += char(event.text.unicode);
							IdxText.setString(UserInput_Idx);
						}
					}
					else if (Keyboard::isKeyPressed(Keyboard::BackSpace)) {
						if (!UserInput_Idx.empty()) {
							UserInput_Idx.erase(UserInput_Idx.size() - 1);
							IdxText.setString(UserInput_Idx);
						}

					}
					else if (Keyboard::isKeyPressed(Keyboard::Space)) {
						string curnum = IdxText.getString();
						if (!curnum.empty()) {
							FinalIdx = stoi(curnum);
							// store the index 
							if (FinalIdx == list.length()) {
								list.push(FinalNumber);
							}
							else {
							list.insert_at(FinalIdx, FinalNumber);
							}
							UserInput_Idx = "";
							IdxText.setString(UserInput_Idx);
						}
							isInserted = 0;
							ValueTyped = 0;
					}

				}
			}
			else if ((cursor.getPosition(Listwindow).x >= 1203 && cursor.getPosition(Listwindow).x <= 1276 && cursor.getPosition(Listwindow).y >= 503 && cursor.getPosition(Listwindow).y <= 533 && Mouse::isButtonPressed(Mouse::Left))) {
				isAppended = 1;
			}
			else if ((cursor.getPosition(Listwindow).x >= 1203 && cursor.getPosition(Listwindow).x <= 1276 && cursor.getPosition(Listwindow).y >= 552 && cursor.getPosition(Listwindow).y <= 582 && Mouse::isButtonPressed(Mouse::Left)))
			{
				isFinded = 1;
			}
			else if ((cursor.getPosition(Listwindow).x >= 1203 && cursor.getPosition(Listwindow).x <= 1276 && cursor.getPosition(Listwindow).y >= 604 && cursor.getPosition(Listwindow).y <= 634 && Mouse::isButtonPressed(Mouse::Left)))
			{
				isDeleted = 1;
			}
			else if ((cursor.getPosition(Listwindow).x >= 453 && cursor.getPosition(Listwindow).x <= 526 && cursor.getPosition(Listwindow).y >= 552 && cursor.getPosition(Listwindow).y <= 582 && Mouse::isButtonPressed(Mouse::Left)))
			{
				isInserted = 1;
			}
			/*else if (Mouse::isButtonPressed(Mouse::Left)) {
				cout << cursor.getPosition(Listwindow).x << " " << cursor.getPosition(Listwindow).y << endl;
			}*/
			/*else if (Keyboard::isKeyPressed(Keyboard::Key::I))
			{
				list.insert_at(5, 1);
			}*/
		

		}
		Listwindow.clear();
		Listwindow.draw(background);
		Listwindow.draw(Append_btn);
		Listwindow.draw(Find_btn);
		Listwindow.draw(delete_btn);
		Listwindow.draw(insert_btn);
		Listwindow.draw(Textbox);
		Listwindow.draw(Posbox);
		Listwindow.draw(Valuebox);
		Listwindow.draw(UserText);
		Listwindow.draw(IdxText);
		list.draw_N_move(Listwindow);
		Listwindow.display();
	}
}