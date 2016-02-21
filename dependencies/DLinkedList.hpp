
#if !defined _DLinkedList
#define _DLinkedList

#include "DLinkedNode.hpp"
#include "../common/Application.hpp"

#include "SelectionSort.hpp"
#include "BubbleSort.hpp"
#include "MergeSort.hpp"
#include "QuickSort.hpp"

#include "benchmark.h"


template <class T> class DLinkedList {
	
	protected:

	DLinkedNode<T> * cursor;
	DLinkedNode<T> * front;
	DLinkedNode<T> * back;

	int length;

	SelectionSort<T> *selectionSort;
	BubbleSort<T> *bubbleSort;
	MergeSort<T> *mergeSort;
	QuickSort<T> *quickSort;
	
	struct benchmark sortBenchmark;

	DLinkedNode<T> * createNode(T value, DLinkedNode<T> * prev = nullptr, DLinkedNode<T> * next = nullptr){
		return new DLinkedNode<T>(value, prev, next);
	}

	void initCursor(T& value){
		this->cursor = this->createNode(value);
		this->front = this->cursor;
		this->back = this->cursor;
		this->length++;
	}

	public:

	static const int SELECTION_SORT = 1;
	static const int BUBBLE_SORT = 2;
	static const int MERGE_SORT = 3;
	static const int QUICK_SORT = 4;

	DLinkedList(){
		this->cursor = nullptr;
		this->front = nullptr;
		this->back = nullptr;
		this->length = 0;

		this->selectionSort = new SelectionSort<T>(this);
		this->bubbleSort = new BubbleSort<T>(this);
		this->mergeSort = new MergeSort<T>(this);
		this->quickSort = new QuickSort<T>(this);

	}

	static void destroy(DLinkedList *l){
		l->clear();

		delete l;
	}

	T getValue(){

		if(this->isEmpty()){
			return this->getNullValue();
		}

		return this->cursor->getValue();
	}

	bool insertBefore(T value){

		if(this->isEmpty()){
			this->initCursor(value);
			return true;
		}

		this->cursor = this->createNode(value, this->cursor->getPrev(), this->cursor);

		this->cursor->getNext()->setPrev(this->cursor);

		if(this->cursor->getPrev() != nullptr){
			this->cursor->getPrev()->setNext(this->cursor);
		} else{
			this->front = this->cursor;
		}

		this->length++;

		return true;
	}

	
	bool insertAfter(T value){

		if(this->isEmpty()){
			this->initCursor(value);
			return true;
		}

		this->cursor = this->createNode(value, this->cursor, this->cursor->getNext());

		this->cursor->getPrev()->setNext(this->cursor);

		if(this->cursor->getNext() != nullptr){
			this->cursor->getNext()->setPrev(this->cursor);
		} else{
			this->back = this->cursor;
		}

		this->length++;

		return true;
	}

	bool remove(bool toNext = true){
		if(this->isEmpty()){
			return false;
		}

		if(this->length == 1){

			DLinkedNode<T>::destroy(this->cursor);

			this->cursor = nullptr;
			this->front = nullptr;
			this->back = nullptr;
			this->length = 0;

			return true;
		}

		if(this->cursor == this->front){

			this->front = this->cursor->getNext();
			this->front->setPrev(nullptr);

		}else if(this->cursor == this->back){

			this->back = this->cursor->getPrev();
			this->back->setNext(nullptr);

		}else{
			this->cursor->getPrev()->setNext(this->cursor->getNext());
			this->cursor->getNext()->setPrev(this->cursor->getPrev());
		}

		this->length--;

		DLinkedNode<T> *cursor = this->cursor;

		if(toNext){
			this->cursor = cursor->getNext() != nullptr ? cursor->getNext() : cursor->getPrev();
		}
		else{
			this->cursor = cursor->getPrev() != nullptr ? cursor->getPrev() : cursor->getNext();
		}

		DLinkedNode<T>::destroy(cursor);

		return true;
	}
	

	bool moveToNext(int length = 1){
		if(this->isEmpty()){
			return false;
		}

		if(this->cursor == this->back){
			return false;
		}

		if(length <= 1){
			this->cursor = this->cursor->getNext();
			return true;
		}

		DLinkedNode<T> *cursor = this->cursor;
		int i;

		for(i = 0; i < length; i++){
			if(!this->moveToNext(1)){
				this->cursor = cursor;
				return false;
			}
		}

		return true;
	}
	
	bool moveToPrev(int length = 1){

		if(this->isEmpty()){
			return false;
		}

		if(this->cursor == this->front){
			return false;
		}

		if(length <= 1){
			this->cursor = this->cursor->getPrev();
			return true;
		}

		DLinkedNode<T> *cursor = this->cursor;
		int i;

		for(i = 0; i < length; i++){
			if(!this->moveToPrev(1)){
				this->cursor = cursor;
				return false;
			}
		}
		
		return true;
	}

	bool moveToFirst(){
		if(this->isEmpty()){
			return false;
		}

		this->cursor = this->front;
		return true;
	}

	bool moveToLast(){
		if(this->isEmpty()){
			return false;
		}

		this->cursor = this->back;
		return true;
	}

	T getNullValue(){
		return (T) 0;
	}

	bool isEmpty(){
		return this->length <= 0;
	}

	int getLength(){
		return this->length;
	}

	void clear(){
		this->moveToFirst();

		while(!this->isEmpty()){
			this->remove();
		}
	}

	bool isLast(){
		return this->cursor == this->back;
	}

	bool isFirst(){
		return this->cursor == this->front;
	}

	void sort(int sortType = DLinkedList::SELECTION_SORT){

		switch(sortType){

			case DLinkedList::SELECTION_SORT:
				this->selectionSort->sort();
				this->sortBenchmark = this->selectionSort->bResult;
			break;

			case DLinkedList::BUBBLE_SORT:
				this->bubbleSort->sort();
				this->sortBenchmark = this->bubbleSort->bResult;
			break;

			case DLinkedList::MERGE_SORT:
				this->mergeSort->sort();
				this->sortBenchmark = this->mergeSort->bResult;
			break;

			case DLinkedList::QUICK_SORT:
				this->quickSort->sort();
				this->sortBenchmark = this->quickSort->bResult;
			break;
		}

	}


	struct benchmark getSortBenchmark(){
		return this->sortBenchmark;
	}

	void swapNodeValues(DLinkedNode<T> *node1, DLinkedNode<T> *node2){
		T temp = node1->getValue();

		node1->setValue(node2->getValue());
		node2->setValue(temp);
	}


	DLinkedNode<T> *getCursorNode(){
		return this->cursor;
	}

	T *toArray(bool clear = true){

		int i = 0;
		int length = this->length;

		T *arrayValues = new T[length];

		this->moveToFirst();

		for (i = 0; i < length; i++){
			arrayValues[i] = this->getValue();

			if(clear){
				this->remove();
			}
			else{
				this->moveToNext();
			}
		}

		return arrayValues;
	}

	void insertFromArray(T values[], int length, bool after = true){
		int i;

		for (i = 0; i < length; i++){
			if(after){
				this->insertAfter(values[i]);
			}else{
				this->insertBefore(values[i]);
			}
			
		}		
	}

	void print(){
		DLinkedNode<T> *c = this->front;

		do{
			std::cout << c->getValue() << " - ";

			c = c->getNext();
		}while(c != nullptr);

		std::cout << "\b\b \n";
	}
};

#endif

