#pragma once
#include "Node.h"
#include <string>
using std::string;

class Stack
{
public:
	Stack() { pTop = NULL; }
	~Stack() {}
	void push(Node<string>* &new_node);
	string pop(void);
	string peek(void);
	bool is_empty(void);

private:
	Node<string> *pTop;
};

void Stack::push(Node<string>* &new_node)
{
	new_node->set_next(pTop);
	pTop = new_node;
	
}

string Stack::pop(void)
{
	string data = pTop->get_data();
	Node<string>* temp = pTop;
	pTop = pTop->get_next();
	delete temp;
	return data;
}

string Stack::peek(void)
{
	return pTop->get_data();
}

bool Stack::is_empty()
{
	if (pTop == NULL) return true;
	else return false;
}
