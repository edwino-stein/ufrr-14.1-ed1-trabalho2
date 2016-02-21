

#if !defined _BubbleSort
#define _BubbleSort


template <class T> class DLinkedList;

#include "DLinkedList.hpp"
#include "DLinkedNode.hpp"

#include "Chronometer.hpp"
#include "benchmark.h"

template <class T> class BubbleSort{
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

	BubbleSort(DLinkedList<T> *list){
		this->list = list;
	}
	
	void sort(){

		int length = this->list->getLength();
		T *values = this->list->toArray();

		this->resetBenchmark();
		Chronometer* chrono = new Chronometer();
		chrono->start();

		bool swapped = true;
		int cursor = 0;
		int bigger = length - 1;

		while(swapped){

			swapped = false;
			cursor = 0;

			while(cursor != bigger){
				if(values[cursor] > values[cursor + 1]){
					this->swapValues(&values[cursor], &values[cursor + 1]);
					swapped = true;
					this->bResult.moves++;
				}

				this->bResult.compareds++;
				cursor++;
			}

			bigger--;
		}

		chrono->pause();
		this->bResult.time = chrono->getResultTime();
		this->bResult.timeUnity = chrono->getUnity();

		this->list->clear();
		this->list->insertFromArray(values, length);
	}
};


#endif