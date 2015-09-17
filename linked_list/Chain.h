#include <iostream>
#include <string>
using std::cout;

#ifndef CHAIN
#define CHAIN

struct PNdata;

template<class T> class Chain;

template<class T>
class ChainNode
{
friend class Chain<T>;
private:
	T data;
	ChainNode<T>* link;

public:
	ChainNode();
	ChainNode(const T& inpData);
	ChainNode(const ChainNode<T>& ref);
	~ChainNode();

	T getData() const;
	const ChainNode<T>* getLink() const;
	void printData() const;
};

template<class T>
class Chain
{
private:
	ChainNode<T>* first;
public:
	Chain();
	Chain(const ChainNode<T>& inpNode);
	Chain(const T& inpData);
	Chain(const Chain<T>& ref);
	~Chain();

	void insertOrderd(const T& insData);
	void insertOrderd(const ChainNode<T>& insNode);
//	T* search(const T& target) const;
	void printAll() const;
	void removeNode(T target);
};


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
template<class T>
T ChainNode<T>::getData() const
{
	return data;
}
template<class T>
const ChainNode<T>* ChainNode<T>::getLink() const
{
	return link;
}
template<class T>
void ChainNode<T>::printData() const
{
	cout << data;
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
	delete first;
}
template<class T>
void Chain<T>::insertOrderd(const T &insData)
{
	ChainNode<T>* insNode = new ChainNode<T>(insData);
	ChainNode<T>* currentNode = first;

	while(currentNode->link!=0 && (currentNode->link)->data<insData)
		currentNode = currentNode->link;
	insNode->link = currentNode->link;
	currentNode->link = insNode;
}
template<class T>
void Chain<T>::insertOrderd(const ChainNode<T>& insNode)
{
	ChainNode<T>* currendNode = first;

	while(currentNode->link!=0 && (currentNode->link)->data<insData)
		currentNode = currentNode->link;
	insNode->link = currnetNode->link;
	currntNode->link = insNode;
}
//template<class T>
//T* Chain<T>::search(const T& target) const
//{
//	ChainNode<T>* currentNode = first->link;
//	while(currentNode!=0)
//	{
//		if(currentNode->data == target)
//			return currentNode->data;
//	}
//	return 0;
//}
template<class T>
void Chain<T>::printAll() const
{
	ChainNode<T>* currentNode = first->link;
	while(currentNode!=0)
	{
		currentNode->printData();
		cout << endl;
		currentNode = currentNode->link;
	}
}
template<class T>
void Chain<T>::removeNode(T target)
{
	ChainNode<T>* preNode = first;
	ChainNode<T>* currentNode = first->link;
	while(currentNode!=0)
	{
		if(currentNode->data == target)
		{
			preNode->link = currentNode->link;
			break;
		}
		preNode = currentNode;
		currentNode = currentNode->link;
	}
}
#endif

