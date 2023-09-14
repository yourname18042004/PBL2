#ifndef LINKLIST_H
#define LINKLIST_H

#include <iostream>

template <typename T> class Node
{
	T* data;
	Node<T>* previous;
	Node<T>* next;
public:
	Node(T* data)
	{
		this->data = data;
	}

	void setPrevious(Node* node)
	{
		previous = node;
	}

	Node<T>* getPrevious() { return previous; }
	Node<T>* getNext() { return next; }

	void setNext(Node<T>* node)
	{
		next = node;
	}

	void setData(T* data)
	{
		this->data = data;
	}

	T* getData()
	{
		return data;
	}
};

template <typename T> class ObjectLinkList
{
private:
	Node<T>* nodeHead;
	Node<T>* nodeTail;

	Node<T>* nodeIndex;

public:

	ObjectLinkList()
	{
		nodeHead = NULL;
		nodeTail = NULL;
		nodeIndex = NULL;
	}

	bool isEmpty()
	{
		return nodeHead == NULL;
	}

	void push(T* data)
	{
		if (isEmpty())
		{
			nodeHead = new Node<T>(data);
			nodeIndex = nodeHead;
			nodeTail = nodeHead;

			nodeIndex->setPrevious(NULL);
			nodeIndex->setNext(NULL);
		}
		else
		{
			std::cout << "Next";
			Node<T>* newNode = new Node<T>(data);
			newNode->setPrevious(nodeTail);
			newNode->setNext(NULL);
			nodeTail->setNext(newNode);
			nodeTail = newNode;
		}
	}

	T pop()
	{

	}

	T popIndex() // lay va xoa
	{

	}

	void resetIndex()
	{
		nodeIndex = nodeHead;
	}
	bool setIndex()
	{
		return nodeIndex == NULL;
	}
	Node<T>* getIndex() // chi lay ko xoa
	{
		Node<T>* node = nodeIndex;
		nodeIndex = nodeIndex->getNext();
		return node;
	}
};


#endif // !LINKLIST_H
