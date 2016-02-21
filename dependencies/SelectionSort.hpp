

#if !defined _SelectionSort
#define _SelectionSort


template <class T> class DLinkedList;

#include "DLinkedList.hpp"
#include "DLinkedNode.hpp"
#include "Chronometer.hpp"
#include "benchmark.h"

template <class T> class SelectionSort{
	protected:

	DLinkedList<T> *list;

	void resetBenchmark(){
		this->bResult.time = 0;
		this->bResult.timeUnity = 0;
		this->bResult.compareds = 0;
		this->bResult.moves = 0;
	}

	void swapValues(T *value1, T* value2){
		T aux = *value1;
		*value1 = *value2;
		*value2 = aux;
	}

	public:
	
	struct benchmark bResult;

	SelectionSort(DLinkedList<T> *list){
		this->list = list;
	}
	
	void sort(){

		int length = this->list->getLength();
		T *values = this->list->toArray();

		this->resetBenchmark();
		Chronometer* chrono = new Chronometer();
		chrono->start();

		int i, j;

		for(i = 0; i < length; i++){

			for(j = i + 1; j < length; j++){
				if(values[i] > values[j]){
					this->swapValues(&values[i], &values[j]);
					this->bResult.moves++;
				}
				this->bResult.compareds++;
			}
		}

		chrono->pause();
		this->bResult.time = chrono->getResultTime();
		this->bResult.timeUnity = chrono->getUnity();

		this->list->clear();
		this->list->insertFromArray(values, length);
	}
};


#endif