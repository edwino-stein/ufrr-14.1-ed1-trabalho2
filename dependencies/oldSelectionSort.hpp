

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

	public:
	
	struct benchmark bResult;

	SelectionSort(DLinkedList<T> *list){
		this->list = list;
	}
	
	void sort(){

		this->resetBenchmark();
		Chronometer* chrono = new Chronometer();
		chrono->start();

		this->list->moveToFirst();

		DLinkedNode<T> * smaller = this->list->getCursorNode();
		DLinkedNode<T> * cursor;

		do{
			cursor = smaller->getNext();
			while(cursor != nullptr){
				if(cursor->getValue() < smaller->getValue()){
					this->list->swapNodeValues(smaller, cursor);
					this->bResult.moves++;
				}

				this->bResult.compareds++;
				cursor = cursor->getNext();
			}

			smaller = smaller->getNext();

		}while(smaller != nullptr);

		chrono->pause();

		this->bResult.time = chrono->getResultTime();
		this->bResult.timeUnity = chrono->getUnity();
	}
};


#endif