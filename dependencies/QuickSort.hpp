

#if !defined _QuickSort
#define _QuickSort


template <class T> class DLinkedList;

#include "DLinkedList.hpp"
#include "DLinkedNode.hpp"

#include "Chronometer.hpp"
#include "benchmark.h"

template <class T> class QuickSort{
	protected:

	DLinkedList<T> *list;

	void swapValues(T *value1, T* value2){
		T aux = *value1;
		*value1 = *value2;
		*value2 = aux;
	}

	void resetBenchmark(){
		this->bResult.time = 0;
		this->bResult.timeUnity = 0;
		this->bResult.compareds = 0;
		this->bResult.moves = 0;
	}

	public:
	
	struct benchmark bResult;

	QuickSort(DLinkedList<T> *list){
		this->list = list;
	}
	
	void sort(){
		
		int length = this->list->getLength();
		T *values = this->list->toArray();

		this->resetBenchmark();
		Chronometer* chrono = new Chronometer();
		chrono->start();

		this->sort(values, 0, length);

		chrono->pause();
		this->bResult.time = chrono->getResultTime();
		this->bResult.timeUnity = chrono->getUnity();

		this->list->clear();
		this->list->insertFromArray(values, length);

		delete [] values;
	}

	void sort(T values[], int left, int right){

		int middle = values[(left + right)/2];
		int leftCursor = left;
		int rightCursor = right;

		while(leftCursor <= rightCursor){

			while(leftCursor < right && values[leftCursor] < middle){
				leftCursor++;
				this->bResult.compareds++;
			}

			while(rightCursor > left && values[rightCursor] > middle){
				rightCursor--;
				this->bResult.compareds++;
			}

			if(leftCursor <= rightCursor){
				this->swapValues(&values[leftCursor], &values[rightCursor]);
				leftCursor++;
				rightCursor--;

				this->bResult.moves++;
			}
		}

		if(rightCursor > left){
			this->sort(values, left, rightCursor);
		}

		if(leftCursor < right){
			this->sort(values, leftCursor, right);
		}
	}
};


#endif