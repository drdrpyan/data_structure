#ifndef __MINHEAP__
#define __MINHEAP__

template<class T>
class MinHeap
{
private:
	T* heap;
	int heapSize;
	int capacity;

public:
	MinHeap(int theCapacity = 10);
	MinHeap(const MinHeap& ref);
	bool operator=(const MinHeap& ref);

	bool IsEmpty() const;
	void Push(const T& e);
	void Pop();
	int getHeapSize() const;
	T operator[](int idx) const;
	
	void ChangeSize1D(T* begin, int currSize, int newSize);
};

template<class T>
MinHeap<T>::MinHeap(int theCapacity = 10)
{
	if(theCapacity<1)
		return;
	capacity=theCapacity;
	heapSize=0;
	heap=new T[capacity+1];
}

template<class T>
MinHeap<T>::MinHeap(const MinHeap& ref) : heapSize(ref.heapSize), capacity(ref.capacity)
{
	heap = new T[ref.capacity];
	for(int i=1; i<ref.heapSize; ++i)
		heap[i] = ref.heap[i];
}

template<class T>
bool MinHeap<T>::operator=(const MinHeap& ref)
{
	heapSize = ref.heapSize;
	capacity = ref.capacity;
	heap = new T[ref.capacity];
	for(int i=1; i<ref.heapSize; ++i)
		heap[i] = ref.heap[i];
}

template<class T>
bool MinHeap<T>::IsEmpty() const
{
	if(heapSize)
		return false;
	else
		return true;
}

template<class T>
void MinHeap<T>::Push(const T& e)
{
	if(heapSize==capacity)
	{
		ChangeSize1D(heap, capacity, capacity*2);
		capacity *= 2;
	}

	int currentNode = ++heapSize;
	while(currentNode!=1 && heap[currentNode/2]>e)
	{
		heap[currentNode] = heap[currentNode/2];
		currentNode /= 2;
	}
	heap[currentNode] = e;
}

template<class T>
void MinHeap<T>::Pop()
{
	if(IsEmpty())
		return;

	heap[1].~T();
	T lastElement = heap[heapSize--];

	int currentNode = 1;
	int child = 2;
	while(child <= heapSize)
	{
		if(child<heapSize && heap[child]>heap[child+1])
			child++;
		if(lastElement <= heap[child])
			break;
		heap[currentNode] = heap[child];
		currentNode=child;
		child *= 2;
	}
	heap[currentNode] = lastElement;
}

template<class T>
int MinHeap<T>::getHeapSize() const
{
	return heapSize;
}

template<class T>
T MinHeap<T>::operator[](int idx) const
{
	return heap[idx];
}

template<class T>
void MinHeap<T>::ChangeSize1D(T* begin, int currSize, int newSize)
{
	T* temp = new T[newSize];
	for(int i=1; i<=heapSize; ++i)
		temp[i] = begin[i];
	
	delete begin;
	begin = temp;
}

#endif