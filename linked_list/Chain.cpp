#include "Chain.h"
#ifndef CHAIN_DEFINITION
#define CHAIN_DEFINITION

//ChainNode
template<class T>
ChainNode<T>::ChainNode() : link(0)
{
}
template<class T>
ChainNode<T>::ChainNode(const T& inpData) : data(T(inpData)), link(0)
{
}
template<class T>
ChainNode<T>::ChainNode(const ChainNode<T> &ref) : data(T(ref.data)), link(ref.link)
{
}
template<class T>
ChainNode<T>::~ChainNode()
{
	if(link == 0)
		return;
	else
	{
		link->~ChainNode();
		delete link;
	}
}

//Chain
template<class T>
Chain<T>::Chain(void)
{
	first = new ChainNode<T>;
	first->link = 0;
}
template<class T>
Chain<T>::Chain(const T &inpData)
{
	first = new ChainNode<T>(inpData);
}
template<class T>
Chain<T>::Chain(const ChainNode<T> &inpNode)
{
	first = new ChainNode<T>(inpNode);
	while(currentNode.link != 0)
	{
		currentNode.link = new ChainNode(currentNode.link);
		currentNode = currentNode.link;
	}
}
template<class T>
Chain<T>::Chain(const Chain<T> &ref)
{
	first = new ChainNode(ref.first);
	ChainNode currentNode = first;
	while(currentNode.link != 0)
	{
		currentNode.link = new ChainNode(currentNode.link);
		currentNode = currentNode.link;
	}
}
template<class T>
Chain<T>::~Chain()
{
	first->~T();
	delete first;
}
template<class T>
void Chain<T>::insertOrderd(const T &insData)
{
	ChainNode<T>* insNode = new ChainNode<T>(insData);
	ChainNode<T>* currendNode = first;

	while(currentNode->link!=0 && (currentNode->link)->data<insData) ;
	insNode->link = currnetNode->link;
	currntNode->link = insNode;
}
template<class T>
void Chain<T>::insertOrderd(const ChainNode<T>& insNode)
{
	ChainNode<T>* currendNode = first;

	while(currentNode->link!=0 && (currentNode->link)->data<insData) ;
	insNode->link = currnetNode->link;
	currntNode->link = insNode;
}

#endif