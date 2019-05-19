#pragma once


template <class T>
class Node
{
public:
	Node() { pNext = nullptr; }
	~Node() {}

	T get_data(void) { return data; }
	void set_data(T new_data) { data = new_data; }
	Node *get_next(void) { return pNext; }
	void set_next(Node *new_next) { pNext = new_next; }

	Node *make_node(T new_data) 
	{
		Node *new_node = new(Node); new_node->set_data(new_data); return new_node;
	}
		
private:
	Node * pNext;
	T data;
};