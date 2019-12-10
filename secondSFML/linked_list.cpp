#include "linked_list.h"
#include <cmath>
Node::Node()
{
	value = 0;
	next = NULL;
	circle.setScale(0.1, 0.1);
	arrow.setScale(0, 0.1);
}
Node::Node(int val)
{
	value = val;
	next = NULL;
	circle.setScale(0.1, 0.1);
	arrow.setScale(0, 0.1);
}
LinkedList::LinkedList()
{
	head = tail = inserted = deleted = appended = checked = NULL;
	Size = 0 , shifting_rate = 0;
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
		if (head == NULL)
		{
			head = tail = appended;
		}
		else
		{
			tail->next = appended;
			tail->arrow.setTexture(arrow_texture);
			tail->arrow.setPosition(50+(Size-1)*dist_between_nodes,310);
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
		if (pos < Size)
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
			inserted->arrow.setPosition(50+ inserted->circle.getPosition().x, inserted->circle.getPosition().y);
			inserted->num.setPosition((1 + pos) * dist_between_nodes, 10);
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
	if (inserted == NULL && deleted == NULL && appended == NULL && found==-1)
	{
		found = target;
		checked = head;
	}
}

void LinkedList::push_annimation()
{
	if (appended == head && appended->circle.getPosition().x < Size * dist_between_nodes)
	{
		appended->circle.move(0.8, 0);
		appended->num.move(0.8, 0);
	}
	else if (appended != head && appended->circle.getPosition().x > Size* dist_between_nodes)
	{
		appended->circle.move(-0.8, 0);
		appended->num.move(-0.8, 0);
	}
	else
		appended = NULL;

}

void LinkedList::insert_annimation()
{
	Node* temp = inserted->next;
	
	
	shifting_rate += 0.8;
	while (temp != NULL && shifting_rate < dist_between_nodes)
	{
		temp->circle.move(0.8, 0);
		temp->num.move(0.8, 0);
		temp->arrow.move(0.8, 0);
		temp = temp->next;
	}
	if (inserted->circle.getPosition().y > 310)
	{
		inserted = NULL;
		shifting_rate = 0;
	}
	else if (shifting_rate >= dist_between_nodes)
	{
		inserted->circle.move(0, 0.8);
		inserted->num.move(0, 0.8);
		inserted->arrow.setTexture(arrow_texture);


		///////////////////EL4O8L BTA3 ROTATE ELARROW ELMAFROOD YEB2A HENA
		temp = head;

		// momken ne3melha PRE node
		while (temp->next != inserted) temp = temp->next;
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
		deleted->circle.move(0, -0.8);
		deleted->num.move(0, -0.8);
	}
	else if (shifting_rate < dist_between_nodes)
	{
		shifting_rate += 0.8;
		Node* temp = deleted->next;
		while (temp != NULL)
		{
			temp->circle.move(-0.8, 0);
			temp->num.move(-0.8, 0);
			temp->arrow.move(-0.8, 0);
			temp = temp->next;
		}
	}
	else
	{
		shifting_rate = 0;
		if (deleted != head)
		{
			Node* temp = head;
			while (temp->next != deleted)
			{
				temp = temp->next;
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
		if (temp != tail )
		{
			if (temp->arrow.getScale().x < 0.1 && appended== NULL)
				temp->arrow.setScale(temp->arrow.getScale().x + 0.001, 0.1);
			window.draw(temp->arrow);
		}
		
		
		temp = temp->next;
	}
}

