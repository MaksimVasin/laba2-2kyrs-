#include <iostream>
#include "Linkedlist.h"
#include  <stdexcept>
#include <string>

LinkedList::LinkedList(char data) // creating a list WITH data
{
	head = new Node;
	head->data = data;
	tail = head;
	sizeList++;
}
LinkedList::LinkedList() // creating a list WITHOUT data
{
	tail = NULL;
	head = NULL;
	sizeList = 0;
}
LinkedList::~LinkedList()
{
	clear();
}
char LinkedList::at(size_t pos)
{
	if (isEmpty()) throw std::out_of_range("The list is empty");
	if (pos + 1 > sizeList) throw std::out_of_range("Index is greater than list size");
	else
	{
		Node* current = head;
		for (size_t position = 0; position < pos; position++) // go to the desired list position
		{
			current = current->next;
		}
		return current->data;
	}
}
bool LinkedList::find(char data)
{
	Node* current = head;
	while (current != nullptr)
	{
		if (current->data == data)
		{
			frequency_add(current);
			return true;
		}
		current = current->next;
	}
	return false;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////// NEW
LinkedList::Node* LinkedList::findNode(char data)
{
	Node* current = head;
	while (current != nullptr)
	{
		if (current->data == data)
		{
			return current;
		}
		current = current->next;
	}
	return nullptr;
}
std::string LinkedList::findcode(char data)
{
	if (find(data)) return findNode(data)->code;
	else {
		throw std::out_of_range("not find");
		return "";
	}
}
bool LinkedList::find(std::string str)
{
	Node* current = head;
	while (current != nullptr)
	{
		if (current->code == str)
		{
			return true;
		}
		current = current->next;
	}
	return false;
}
char LinkedList::findSymbol(std::string str)
{
	Node* current = head;
	while (current != nullptr)
	{
		if (current->code == str)
		{
			return current->data;
		}
		current = current->next;
	}
	throw std::out_of_range("not find");
}
void LinkedList::CodingNode(char data, bool one)
{
	Node* cur = findNode(data);
	if (cur != nullptr)
	{
		if (one) cur->code.push_back('1');
		else cur->code.push_back('0');
	}
}
void LinkedList::my_swap(Node *node1, Node *node2)
{
	Node* buf = new Node;
	buf->data = node1->data;
	buf->frequency = node1->frequency;
	node1->data = node2->data;
	node1->frequency = node2->frequency;
	node2->data = buf->data;
	node2->frequency = buf->frequency;
	delete buf;
}
void LinkedList::bubbleSort()
{
	Node* cur_j;
	if (head != tail)
	{
		for (size_t i = 0; i < sizeList - 1; i++)
		{
			cur_j = head;
			do
			{
				if (cur_j->next->frequency > cur_j->frequency)
					my_swap(cur_j->next, cur_j);
				cur_j = cur_j->next;
			} while (cur_j != tail);
		}
	}
}
Iterator* LinkedList::create_iterator()
{
	return new iterator(head);
}
bool LinkedList::iterator::has_cur()
{
	return (cur != nullptr);
}
void LinkedList::iterator::next()
{
	cur = cur->next;
}
int LinkedList::iterator::freq()
{
	return cur->frequency;
}
char LinkedList::iterator::symbol()
{
	return cur->data;
}
std::string LinkedList::iterator::code()
{
	return cur->code;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LinkedList::clear() // deleting all list items
{
	if (isEmpty()); //throw std::out_of_range("The list is empty");
	else
	{
		while (sizeList != 0)
		{
			pop_back();
		}
	}
}

size_t LinkedList::get_size()
{
	return sizeList;
}

void LinkedList::insert(char data, size_t pos)
{
	if (sizeList == 0) throw std::out_of_range("The list is empty");
	if (pos + 1 > sizeList) throw std::out_of_range("Index is greater than list size");
	else
	{
		Node* current = head;
		if (pos == 0)
		{
			push_front(data);
		}
		else
		{
			for (size_t position = 0; position < pos; position++)
			{
				current = current->next;
			}
			Node* InsertElem = new Node;
			InsertElem->prev = current->prev;
			InsertElem->next = current;
			current->prev->next = InsertElem;
			current->prev = InsertElem;
			InsertElem->data = data;
			sizeList++;
		}
	}
};

bool LinkedList::isEmpty()
{
	if (sizeList == 0) return true;
	else return false;
}

void LinkedList::pop_back()
{
	if (sizeList == 0) throw std::out_of_range("The list is empty");
	else if (sizeList == 1)
	{
		delete tail;
		sizeList--;
	}
	else // if SizeList != 0,1
	{
		Node* current = tail;
		current->prev->next = NULL;
		tail = current->prev;
		delete current;
		sizeList--;
	}
}

void LinkedList::pop_front()
{
	if (isEmpty()) throw std::out_of_range("The list is empty");
	else if (sizeList == 1)
	{
		delete head;
		sizeList--;
	}
	else // if SizeList != 0,1
	{
		Node* current = head;
		head = current->next;
		current->next->prev = NULL;
		delete current;
		sizeList--;
	}
}

void LinkedList::print_to_console()
{
	if (isEmpty())
	{
		std::cout << "\n\"The list is empty\"\n";
	}
	else
	{
		Node* current = head;
		for (size_t position = 0; position < sizeList; position++)
		{
			std::cout << " | " <<  current->data << " | amount - " << current->frequency << "| code - "  << current->code << " |\n";
			current = current->next;
		}
		//std::cout << "\n\nSizeList: " << sizeList << "\n";
	}
}

void LinkedList::push_back(char data)
{
	if (isEmpty()) // if the list is empty
	{
		head = new Node;
		head->data = data;
		tail = head;
	}
	else
	{
		tail->next = new Node;
		tail->next->prev = tail;
		tail = tail->next;
		tail->data = data;
	}
	sizeList++;
}
void LinkedList::push_back(char data, int frequency)
{
	if (isEmpty()) // if the list is empty
	{
		head = new Node;
		head->data = data;
		head->frequency = frequency;
		tail = head;
	}
	else
	{
		tail->next = new Node;
		tail->next->prev = tail;
		tail = tail->next;
		tail->data = data;
		tail->frequency = frequency;
	}
	sizeList++;
}

void LinkedList::push_front(char data)
{
	if (isEmpty()) // if the list is empty
	{
		head = new Node;
		head->data = data;
		tail = head;
	}
	else
	{
		head->prev = new Node;
		head->prev->next = head;
		head = head->prev;
		head->data = data;
	}
	sizeList++;
}

void LinkedList::remove(size_t pos)
{
	if (sizeList == 0) throw std::out_of_range("The list is empty");
	if (pos + 1 > sizeList) throw std::out_of_range("Index is greater than list size");
	else
	{
		if (pos == 0) // if this is the first element
		{
			pop_front();
		}
		else if (pos == sizeList - 1) // if this is the last element
		{
			pop_back();
		}
		else
		{
			Node* current = head;
			for (size_t position = 0; position < pos; position++) // go to the desired list position
			{
				current = current->next;
			}
			current->prev->next = current->next; // replacement of pointer (next)
			current->next->prev = current->prev; // replacement of pointer (prev)
			delete current;
			sizeList--;
		}
	}
}

void LinkedList::reverse()
{
	char buffer; // auxiliary variable to swap
	Node* current2 = tail;
	Node* current = head;
	if (sizeList == 0) throw std::out_of_range("The list is empty");
	else if (sizeList == 1);
	else
	{
		for (size_t position = 0; position < sizeList / 2; position++)
		{
			if (current->data != current2->data)
			{
				buffer = current2->data;		// swap
				current2->data = current->data; //
				current->data = buffer;         //
			}
			current = current->next; // "current" moves from the head to the center
			current2 = current2->prev; // "current2" moves from the tail to the center
		}
	}
}

void LinkedList::set(char data, size_t pos) // replacing an element by index with the passed element
{
	if (sizeList == 0) throw std::out_of_range("The list is empty");
	if (pos + 1 > sizeList) throw std::out_of_range("Index is greater than list size");
	else
	{
		Node* current = head;
		for (size_t position = 0; position < pos; position++) // go to the desired list position
		{
			current = current->next;
		}
		current->data = data;
	}
}