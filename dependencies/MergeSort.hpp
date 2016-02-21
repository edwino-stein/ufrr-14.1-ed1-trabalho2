

#if !defined _MergeSort
#define _MergeSort


template <class T> class DLinkedList;

#include "DLinkedList.hpp"
#include "DLinkedNode.hpp"

#include "Chronometer.hpp"
#include "benchmark.h"

template <class T> class MergeSort{
	protected:

	DLinkedList<T> *list;
	
	void swapValues(T *value1, T* value2){
		T aux = *value1;
		*value1 = *value2;
		*value2 = aux;
	}

	void merge(T values[], int left, int middle, int right){

		int i, j, cursor;

		int leftBranchSize = middle - left + 1;
		T *leftBranch = new T[leftBranchSize];
		for (i = 0; i < leftBranchSize; i++){
			leftBranch[i] = values[i + left];
			this->bResult.moves++;
		}

 		int rightBranchSize = right - middle;
 		T *rightBranch = new T[rightBranchSize];
 		for (i = 0; i < rightBranchSize; i++){
 			rightBranch[i] = values[i + middle + 1];
 			this->bResult.moves++;
 		}

		for (i = 0, j = 0, cursor = left; cursor <= right; cursor++) {

			if (i == leftBranchSize){

				values[cursor] = rightBranch[j++];
				this->bResult.moves++;

			} else if(j == rightBranchSize) {

				 values[cursor] = leftBranch[i++];
				 this->bResult.moves++;

			} else if (leftBranch[i] < rightBranch[j]){

				values[cursor] = leftBranch[i++];
				this->bResult.moves++;

			} else{

				values[cursor] = rightBranch[j++];
				this->bResult.moves++;

			}

			this->bResult.compareds++;
		}

		delete [] leftBranch;
		delete [] rightBranch;
	}

	void branch (T values[], int left, int right){

		if (left == right){
			return;
		}

		int middle = (left + right) / 2;

		this->branch(values, left, middle);
		this->branch(values, middle + 1, right);

		this->merge(values, left, middle, right);
	}

	void resetBenchmark(){
		this->bResult.time = 0;
		this->bResult.timeUnity = 0;
		this->bResult.compareds = 0;
		this->bResult.moves = 0;
	}

	public:
		
	struct benchmark bResult;

	MergeSort(DLinkedList<T> *list){
		this->list = list;
	}
	
	void sort(){

		int length = this->list->getLength();
		T *values = this->list->toArray();

		this->resetBenchmark();
		Chronometer* chrono = new Chronometer();
		chrono->start();

		this->sort(values, length);

		chrono->pause();
		this->bResult.time = chrono->getResultTime();
		this->bResult.timeUnity = chrono->getUnity();

		this->list->clear();
		this->list->insertFromArray(values, length);

		delete [] values;
	}

	void sort(T values[], int length){
		this->branch(values, 0, length - 1);
	}
};


#endif