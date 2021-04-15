#pragma once
#include <string>
#include "iterator.h";

class LinkedList
{
private:
	struct Node // Node List
	{
		Node(char data = ' ', std::string code = "", Node* prev = nullptr, Node* next = nullptr, size_t frequency = 1)
		{
			this->next = next;
			this->prev = prev;
			this->data = data;
			this->frequency = frequency;
			this->code = code;
		};
		char data;
		std::string code;
		int frequency;
		Node* next; // next element
		Node* prev; // previous element
	};
	size_t sizeList;
	Node* head;
	Node* tail;
public:
	LinkedList(char data); // creating a list WITH data
	LinkedList(); // creating a list WITHOUT data
	~LinkedList();

	void push_back(char data);			 // 1 // add lust element
	void push_back(char data, int frequency);  // bonus // add lust element
	void push_front(char data);			 // 2 // add front element
	void pop_back();					 // 3 // del lust element
	void pop_front();					 // 4 // del front element
	void insert(char data, size_t pos);   // 5 // add by index 
	char at(size_t pos);					 // 6 // getting by index


	///////////////////////////////////////////////////////////NEW METHODS
	bool find(char data);
	bool find(std::string str);
	char findSymbol(std::string);
	Node* findNode(char data);
	std::string findcode(char data);
	void CodingNode(char data, bool one);
	void frequency_add(Node* cur) { cur->frequency++; };
	void my_swap(Node* node1, Node* node2);
	void bubbleSort();
	///////////////////////////////////////////////////////////
	
	void remove(size_t pos);			 // 7 // del by index
	size_t get_size();					 // 8 // getting size List
	void print_to_console();			 // 9 // print to console
	void clear();						 // 10// clear list
	void set(char data, size_t pos);		 // 11// swap data
	bool isEmpty();						 // 12// checking if the list is empty
	void reverse();						 // 13// reverse
	void menu(LinkedList List); //function menu

	Iterator* create_iterator();
	class iterator : public Iterator
	{
	public:
		iterator(Node* head)
		{
			cur = head;
		}
		~iterator()
		{
			delete cur;
		};
		bool has_cur() override;
		char symbol() override;
		std::string code() override;
		int freq() override; // frequency
		void next() override;
	private:
		Node* cur;
	};
};