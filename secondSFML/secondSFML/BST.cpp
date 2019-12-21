#include "BST.h"
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
	root = NULL;
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
/*B_Node* BST::findNode(int val)
{
	B_Node* tmp = root;

	while ((tmp != NULL) && (tmp->value != val))
		if (tmp->value > val)
			tmp = tmp->left;
		else
			tmp = tmp->right;
	return tmp;
}

B_Node* BST::findParent(int val)
{
	B_Node* a, * b;
	a = root;
	b = NULL;
	while ((a != NULL) && (a->value != val))
	{
		b = a;
		if (a->value > val)
			a = a->left;
		else
			a = a->right;
	}
	return b;
}

B_Node* BST::findMin(B_Node* start)
{
	B_Node* minNode = start;
	while (minNode->left != NULL)
		minNode = minNode->left;
	return minNode;
}
void BST::remove(int val)
{
	B_Node* n = findNode(val);
	if (n==nullptr)
	{
		cout << "not found" << endl;
		return;
	}
	if ((n->left == NULL) && (n->right == NULL)) //deleting a leaf node
	{
		if (n == root)
			root = NULL;
		else
		{
			B_Node* parent = findParent(val);
			if (val < parent->value)
				parent->left = NULL;
			else
				parent->right = NULL;
		}
		delete n;
	}
	else if ((n->left == NULL) && (n->right != NULL))
	{
		B_Node* parent = findParent(val);
		if (n == root)
			root = n->right;
		else
		{
			if (val < parent->value)
				parent->left = n->right;
			else
				parent->right = n->right;
		}
		delete n;
	}
	else if ((n->left != NULL) && (n->right == NULL))
	{
		B_Node* parent = findParent(val);
		if (n == root)
			root = n->left;
		else
		{
			if (val < parent->value)
				parent->left = n->left;
			else
				parent->right = n->left;
		}
		delete n;
	}
	else
	{
		B_Node* minNode = findMin(n->right);
		B_Node* parent = findParent(minNode->value);
		n->value = minNode->value;
		n->num_text.setString(to_string(minNode->value));
		n->circle.setPosition(minNode->circle.getPosition());
		n->num_text.setPosition(minNode->num_text.getPosition());
		if (parent == n)
			parent->right = minNode->right;
		else
			parent->left = minNode->right;
		delete minNode;
	}
	
}*/




B_Node* BST::remove(B_Node* parent,B_Node* rt, int val)
{
	if (deleted==NULL)
	{
		if (rt == NULL)
		{		cout << "Not Found\n";
			return rt;
		}
		if (val < rt->value)
			rt->left=remove(rt,rt->left, val);

		else if (val > rt->value)
			rt->right=remove(rt,rt->right, val);

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
				/*else
				{
					if (val < parent->value)
						parent->left = rt->right;
					else
						parent->right = rt->right;
				}*/
				B_Node* returning=rt->right;
				delete rt;
				return returning;
			}
			else if ((rt->left != NULL) && (rt->right == NULL))
			{
				if (rt == root)
					root = rt->left;
				/*else
				{
					if (val < parent->value)
						parent->left = rt->left;
					else
						parent->right = rt->left;
				}*/
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
			rt->left=remove(rt, rt->left, val);
	}

	
	rt->update_hight();
	rt=balance(rt);
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
		//	rt->has_left_child = 1;
		//	rt->line_left = drawArrow(rt->circle.getPosition().x, rt->circle.getPosition().y + 2 * 1.5,
			//		rt->left->circle.getPosition().x + 2 * 1.5, rt->left->circle.getPosition().y + 3);
			rt->left->num_text.setPosition(1366 * rt->left->x +10, 780 * rt->left->y / 7 +3);
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
			//rt->has_right_child = 1;
			//rt->line_right = drawArrow(rt->circle.getPosition().x + 2 * 1.5, rt->circle.getPosition().y + 2 * 1.5,
				//rt->right->circle.getPosition().x, rt->right->circle.getPosition().y + 3);
			rt->right->num_text.setPosition(1366 * rt->right->x+10, 780 * rt->right->y / 7 +3);
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
			start->circle.move(2, 0);
			start->num_text.move(2, 0);
		}

		if (start->circle.getPosition().x > 1366 * start->x)
		{
			start->circle.move(-2, 0);
			start->num_text.move(-2, 0);
		}
		if (start->circle.getPosition().y < 780 * start->y / 7)
		{
			start->circle.move(0, 2);
			start->num_text.move(0, 2);
		}
		if (start->circle.getPosition().y > 780 * start->y / 7)
		{
			start->circle.move(0, -2);
			start->num_text.move(0, -2);
		}
	}
	
		if (start->left != NULL)
		{
				start->line_left = drawArrow(start->circle.getPosition().x, start->circle.getPosition().y + 2 * 1.5,
				start->left->circle.getPosition().x + 2 * 1.5, start->left->circle.getPosition().y + 3);
		}
		if (start->right != NULL)
		{
			start->line_right = drawArrow(start->circle.getPosition().x + 2 * 1.5, start->circle.getPosition().y + 2 * 1.5,
				start->right->circle.getPosition().x, start->right->circle.getPosition().y + 3);
		}
	//start->circle.setPosition(1366 * start->x, 780 * start->y / 7);
	//start->num_text.setPosition(1366 * start->x, 780 * start->y / 7);


	if (start->left!=NULL)
		window.draw(start->line_left);
	if (start->right!=NULL)
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

