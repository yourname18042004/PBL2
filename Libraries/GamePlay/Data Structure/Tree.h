#ifndef TREE_H
#define TREE_H
#include <iostream>
#include <vector>

template <typename T> class NodeTree {
	T* data;
	NodeTree<T>* previous;
	std::vector <NodeTree<T>*> NodeData;
public:
	NodeTree(T* data) {
		this->data = data;
	}

	void setPrevious(NodeTree<T>* node)
	{
		previous = node;
	}

	NodeTree<T>* getPrevious()
	{
		return previous;
	}

	void PushNode(NodeTree<T>* node)
	{
		NodeData.push_back(node);
	}

	NodeTree<T>* getNodeIndex(int i) {
		return NodeData[i];
	}

	void setIndex(int i, T* data)
	{
		NodeData[i]->SetData(data);
	}

	void SetData(T* data) {
		this->data = data;
	}
	T* getData() {
		return data;
	}
	int getSize() {
		return NodeData.size();
	}
};


template <typename T> class Tree {
	NodeTree<T>* NodeHead;
	NodeTree<T>* NodeIndex;

public:
	Tree() {
		NodeHead = NULL;
		NodeIndex = NULL;
	}
	bool isEmpty() {
		return NodeHead == NULL;
	}
	
	void Push(T* data)
	{
		if (isEmpty())
		{
			NodeHead = new NodeTree<T>(data);;
			NodeIndex = NodeHead;
			NodeIndex->setPrevious(NULL);
		}

		else
		{
			NodeTree<T>* node = new NodeTree<T>(data);
			NodeIndex->PushNode( node);
			node->setPrevious(NodeIndex);
			
		}
	}

	void NextIndex(int i)
	{
		NodeIndex = NodeIndex->getNodeIndex(i);
	}

	void PreviousIndex()
	{
		NodeIndex = NodeIndex->getPrevious();
	}

	NodeTree<T>* getNodeIndex()
	{
		return NodeIndex;
	}
	void Reset() {
		NodeIndex = NodeHead;
	}
};

#endif