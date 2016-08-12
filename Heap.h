/******************************         Heap.h         ****************************************************
************     该文件是利用堆的相关特性，因为其数据成员中有数组，size，以及容量（capacity）  ************
************     所以在此直接使用C++中Vector用以实现.										   ************
***********************************************************************************************************/
#pragma once  
#include <vector>  
#include<assert.h>  

// 小堆  
template<class T>
struct Less
{
	bool operator() (const T& l, const T& r)
	{
		return l < r;   
	}
};

template<class T>
struct Greater
{
	bool operator() (const T& l, const T& r)
	{
		return l > r;   
	}
};

template<class T, class Compare = Less<T>>
class Heap
{
public:
	Heap()
	{}

	Heap(const T* a, size_t size)
	{
		for (size_t i = 0; i < size; ++i)
		{
			_arrays.push_back(a[i]);
		}

		// 建堆  
		for (int i = (_arrays.size() - 2) / 2; i >= 0; --i)
		{
			AdjustDown(i);
		}
	}

	void Push(const T& x)
	{
		_arrays.push_back(x);
		AdjustUp(_arrays.size() - 1);
	}

	void Pop()
	{
		assert(_arrays.size() > 0);
		swap(_arrays[0], _arrays[_arrays.size() - 1]);
		_arrays.pop_back();

		AdjustDown(0);
	}

	T& Top()
	{
		assert(_arrays.size() > 0);
		return _arrays[0];
	}

	bool Empty()
	{
		return _arrays.empty();
	}

	int Size()
	{
		return _arrays.size();
	}

	void AdjustDown(int root)
	{
		size_t child = root * 2 + 1;
		    
		Compare com;
		while (child < _arrays.size())
		{
			if (child + 1<_arrays.size() &&
				com(_arrays[child + 1], _arrays[child]))
			{
				++child;
			}

			 
			if (com(_arrays[child], _arrays[root]))
			{
				swap(_arrays[child], _arrays[root]);
				root = child;
				child = 2 * root + 1;
			}
			else
			{
				break;
			}
		}
	}

	void AdjustUp(int child)
	{
		int parent = (child - 1) / 2;

		 
		while (child > 0)
		{
			if (Compare()(_arrays[child], _arrays[parent]))
			{
				swap(_arrays[parent], _arrays[child]);
				child = parent;
				parent = (child - 1) / 2;
			}
			else
			{
				break;
			}
		}
	}

	void Print()
	{
		for (size_t i = 0; i < _arrays.size(); ++i)
		{
			cout << _arrays[i] << " ";
		}
		cout << endl;
	}

public:
	/*T* _array;
	size_t _size;
	size_t _capacity;*/
	vector<T> _arrays;
};