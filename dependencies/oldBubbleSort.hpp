

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

	public:
	
	struct benchmark bResult;

	BubbleSort(DLinkedList<T> *list){
		this->list = list;
	}
	
	void sort(){

		this->resetBenchmark();
		Chronometer* chrono = new Chronometer();
		chrono->start();

		DLinkedNode<T> * cursor = nullptr;

		this->list->moveToLast();
		DLinkedNode<T> * bigger = this->list->getCursorNode();

		bool swapped = true;

		while(swapped){

			this->list->moveToFirst();
			cursor = this->list->getCursorNode();
			swapped = false;


			while(cursor != bigger){
				if(cursor->getValue() > cursor->getNext()->getValue()){
					this->list->swapNodeValues(cursor, cursor->getNext());
					swapped = true;
					this->bResult.moves++;
				}

				this->bResult.compareds++;
				cursor = cursor->getNext();
			}

			bigger = bigger->getPrev();
		}
		chrono->pause();

		this->bResult.time = chrono->getResultTime();
		this->bResult.timeUnity = chrono->getUnity();
	}
};


#endif