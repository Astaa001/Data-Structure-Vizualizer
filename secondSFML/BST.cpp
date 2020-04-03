#include"BST.h"
#include<iostream>
using namespace std;

B_Node::B_Node(int val)
{
	value = val;
	hight = 1;
	right = left = NULL;
	circle.setScale(0, 0);
}

B_Node::B_Node(int val, Texture& CR, Font& FNT)
{
	value = val;
	x = y = 0;
	hight = 1;
	right = left = NULL;
	circle.setTexture(CR);
	num_text.setFont(FNT);
	circle.setScale(0, 0);
	
	//	num_text.setScale(0, 0);
}

BST::BST()
{
	root = NULL; speed = 1.2;
	new_node_pos_updated = 0;
	circle_texture.loadFromFile("normal.png");
	num_font.loadFromFile("Crasns.ttf");
}

B_Node* BST::balance(B_Node* rt)
{
	if (rt->balance_factor() > 1)
	{
		if (rt->left->balance_factor() == -1)
			rt->left = rotate_left(rt->left);
		rt = rotate_right(rt);
	}
	else if (rt->balance_factor() < -1)
	{
		if (rt->right->balance_factor() == 1)
			rt->right = rotate_right(rt->right);
		rt = rotate_left(rt);
	}
	return rt;
}

B_Node* BST::remove(B_Node* parent, B_Node* rt, int val)
{
	if (deleted == NULL)
	{
		if (rt == NULL)
		{
			cout << "Not Found\n";
			return rt;
		}
		if (val < rt->value)
			rt->left = remove(rt, rt->left, val);

		else if (val > rt->value)
			rt->right = remove(rt, rt->right, val);

		else
		{
			if ((rt->left == NULL) && (rt->right == NULL)) //deleting a leaf node
			{
				if (rt == root)
					root = NULL;
				/*else
				{
					if (val < parent->value)
						parent->left = NULL;
					else
						parent->right = NULL;
				}
						*/
				delete rt;
				return NULL;
			}
			else if ((rt->left == NULL) && (rt->right != NULL))
			{

				if (rt == root)
					root = rt->right;
				B_Node* returning = rt->right;
				delete rt;
				return returning;
			}
			else if ((rt->left != NULL) && (rt->right == NULL))
			{
				if (rt == root)
					root = rt->left;
				B_Node* returning = rt->left;
				delete rt;
				return returning;
			}
			else
			{
				deleted = rt;
				remove(rt, rt->right, val)->value;
			}
		}
	}
	else
	{
		if (rt->left == NULL)
		{
			deleted->value = rt->value;
			deleted->num_text.setString(to_string(rt->value));
			deleted->circle.setPosition(rt->circle.getPosition());
			deleted->num_text.setPosition(rt->num_text.getPosition());
			if (parent == deleted)
				parent->right = rt->right;
			else
				parent->left = rt->right;
			B_Node* returning = rt->right;
			delete rt;
			deleted = NULL;
			return returning;
		}
		else
			rt->left = remove(rt, rt->left, val);
	}

	rt->update_hight();
	rt = balance(rt);
	return rt;
}

void B_Node::update_hight()
{
	int l = 0, r = 0;
	if (left != NULL)
		l = left->hight;
	if (right != NULL)
		r = right->hight;

	hight = 1 + max(l, r);
}

void BST::update_pos(B_Node* rt, double prev_x, double prev_y)
{
	if (rt == NULL)
		return;
	rt->x = prev_x;
	rt->y = prev_y;
	update_pos(rt->right, prev_x + 1 / pow(2, prev_y + 1), prev_y + 1);
	update_pos(rt->left, prev_x - 1 / pow(2, prev_y + 1), prev_y + 1);
}

int B_Node::balance_factor()
{
	int l = 0, r = 0;
	if (left != NULL)
		l = left->hight;
	if (right != NULL)
		r = right->hight;

	return l - r;
}

B_Node* BST::rotate_left(B_Node* parent)
{
	B_Node* y = parent->right;
	parent->right = y->left;
	y->left = parent;
	parent->update_hight();
	y->update_hight();
	return y;
}
B_Node* BST::rotate_right(B_Node* parent)
{
	B_Node* y = parent->left;
	parent->left = y->right;
	y->right = parent;
	parent->update_hight();
	y->update_hight();
	return y;
}

B_Node* BST::Insert(B_Node* rt, int val)
{
	if (rt == NULL)
	{

		rt = new B_Node(val, circle_texture, num_font);
		rt->num_text.setString(to_string(rt->value));
		return rt;
	}
	if (val < rt->value)
	{
		rt->left = Insert(rt->left, val);

		if (!new_node_pos_updated)
		{
			update_pos(root, 0.5, 1);
			rt->left->circle.setPosition(1366 * rt->left->x, 780 * rt->left->y / 7);
			rt->left->num_text.setPosition(1366 * rt->left->x + 10, 780 * rt->left->y / 7 + 3);  //10
			new_node_pos_updated = 1;
			timer.restart();
		}
	}
	else if (val > rt->value)
	{
		rt->right = Insert(rt->right, val);

		if (!new_node_pos_updated)
		{
			update_pos(root, 0.5, 1);
			rt->right->circle.setPosition(1366 * rt->right->x, 780 * rt->right->y / 7);
			rt->right->num_text.setPosition(1366 * rt->right->x + 10, 780 * rt->right->y / 7 + 3);//10
			new_node_pos_updated = 1;
			timer.restart();
		}
	}
	else
		return rt;

	//AVL
	rt->update_hight();
	rt = balance(rt);
	return rt;
}

RectangleShape BST::drawArrow(float x1, float y1, float x2, float y2)
{
	x1 += 15;
	x2 += 15;
	y1 += 15;
	y2 += 15;
	RectangleShape Line;
	Line.setSize(Vector2f(sqrt(pow(x1 - x2, 2) + pow(y2 - y1, 2)), 4.0f));
	Line.setPosition(Vector2f(x1, y1));
	Line.setFillColor(Color::White);
	float slope = (y2 - y1) / (x2 - x1);
	float PI = 3.14159265;
	if (slope > 0)
		Line.setRotation((atan(slope) * 180) / PI);
	else if (slope < 0)
		Line.setRotation(-(180 - (atan(slope) * 180) / PI));
	return Line;
}
void BST::draw(RenderWindow& window, B_Node* start)
{
	if (start == NULL)
		return;
	if (timer.getElapsedTime().asSeconds() >= 1)
	{
		if (start->circle.getPosition().x < 1366 * start->x)
		{
			start->circle.move(speed, 0);
			start->num_text.move(speed, 0);
		}
		if (start->circle.getPosition().x > 1366 * start->x)
		{
			start->circle.move(-speed, 0);
			start->num_text.move(-speed, 0);
		}
	    if (start->circle.getPosition().y < 780 * start->y / 7)
		{
			start->circle.move(0, speed);
			start->num_text.move(0, speed);
		}
	    if (start->circle.getPosition().y > 780 * start->y / 7)
		{
			start->circle.move(0, -speed);
			start->num_text.move(0, -speed);
		}
	}
	if (start->left != NULL)
	{
		start->line_left = drawArrow(start->circle.getPosition().x, start->circle.getPosition().y,
			start->left->circle.getPosition().x , start->left->circle.getPosition().y);
	}
	if (start->right != NULL)
	{
		start->line_right = drawArrow(start->circle.getPosition().x, start->circle.getPosition().y,
			start->right->circle.getPosition().x, start->right->circle.getPosition().y);
	}
	
	if (start->left != NULL)
		window.draw(start->line_left);
	if (start->right != NULL)
		window.draw(start->line_right);

	window.draw(start->circle);
	window.draw(start->num_text);
	if (start->circle.getScale().x < 0.1)
	{
		start->circle.setScale(start->circle.getScale().x + 0.001, start->circle.getScale().y + 0.001);
		start->num_text.setScale(start->num_text.getScale().x + 0.001, start->num_text.getScale().y + 0.001);
	}
	draw(window, start->left);
	draw(window, start->right);
}
void BST::Show() {
	BST avl;
	Clock clock;
	RenderWindow window(VideoMode(1366, 768), "BST");
	Sprite background;
	Texture background_texture;
	background_texture.loadFromFile("QueueBackground.jpg");
	background.setTexture(background_texture);
	background.setScale(2.2, 2);
	Text UserText;
	UserText.setCharacterSize(30); UserText.setFillColor(Color::White);
	UserText.setFont(num_font); UserText.setStyle(Text::Underlined);
	UserText.setPosition(1100, 66);
	string UserInput; int FinalNumber = 0;
	//insert button
	Sprite insert_btn;
	Texture insert_tex;
	insert_tex.loadFromFile("Insert.png");
	insert_btn.setTexture(insert_tex);
	insert_btn.setPosition(1200, 40);
	insert_btn.setScale(0.1, 0.1);
	//delete button
	Sprite delete_btn;
	Texture delete_tex;
	delete_tex.loadFromFile("Delete.png");
	delete_btn.setTexture(delete_tex);
	delete_btn.setPosition(1200, 85);
	delete_btn.setScale(0.1, 0.1);
	//InputTextbox saeed photoshop lel png
	Sprite Insert_Textbox; Texture Insert_Textbox_texture;
	Insert_Textbox_texture.loadFromFile("TextboxPic.png");
	Insert_Textbox.setTexture(Insert_Textbox_texture);
	Insert_Textbox.setPosition(1050, 45);
	Insert_Textbox.setScale(0.15, 0.18);
	Mouse cursor; 	bool isInserted = 0, isDeleted = 0;
	while (window.isOpen())
	{

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Key::Home)) {
				window.close();
				MainMenu Menu;
				Menu.Show();
			}
			else if (isInserted) {
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
				else if (Keyboard::isKeyPressed(Keyboard::Enter) && clock.getElapsedTime().asMilliseconds() >= 500) {
					string curnum = UserText.getString();
					if (!curnum.empty()) {
						FinalNumber = stoi(curnum);
						avl.root = avl.Insert(avl.root, FinalNumber);
						clock.restart();
						avl.new_node_pos_updated = 0;
						UserInput = "";
						UserText.setString(UserInput);
					}
					isInserted = 0;
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
				else if (Keyboard::isKeyPressed(Keyboard::Enter) && clock.getElapsedTime().asMilliseconds() >= 500) {
					string curnum = UserText.getString();
					if (!curnum.empty()) {
						FinalNumber = stoi(curnum);
						avl.root = avl.remove(NULL, avl.root, FinalNumber);
						clock.restart();
						UserInput = "";
						UserText.setString(UserInput);
					}
					isDeleted = 0;
				}
			}
			else if ((cursor.getPosition(window).x >= 1204 && cursor.getPosition(window).x <= 1276 && cursor.getPosition(window).y >= 88 && cursor.getPosition(window).y <= 117 && Mouse::isButtonPressed(Mouse::Left)))
			{
				isDeleted = 1;
			}
			else if ((cursor.getPosition(window).x >= 1204 && cursor.getPosition(window).x <= 1276 && cursor.getPosition(window).y >= 42 && cursor.getPosition(window).y <= 73 && Mouse::isButtonPressed(Mouse::Left)))
			{
				isInserted = 1;
			}
			else if (Mouse::isButtonPressed(Mouse::Left)) {
				cout << cursor.getPosition(window).x << " " << cursor.getPosition(window).y << endl;
			}
		}

		window.clear();
		window.draw(background);
		window.draw(insert_btn);
		window.draw(delete_btn);
		window.draw(Insert_Textbox);
		window.draw(UserText);
		avl.update_pos(avl.root, 0.5, 1);
		avl.draw(window, avl.root);
		window.display();
	}
}
