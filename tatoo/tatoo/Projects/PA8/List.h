#pragma once
#include "Node.h"

template <class T>
class List
{
public:
	List() { pHead = nullptr; }
	~List() {}

	Node<T> *get_head(void) { return pHead; }
	void set_head(Node<T> *new_head) { pHead = new_head; }

	void insert_af(Node<T> * new_node);

private:
	Node<T> *pHead;
};

template <class T>
void List<T>::insert_af(Node<T> * new_node)
{
	Node<T> *temp = this->pHead;
	this->pHead = new_node;
	new_node->set_next(temp);
}