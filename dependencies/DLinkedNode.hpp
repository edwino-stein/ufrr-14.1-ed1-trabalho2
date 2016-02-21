#if !defined _DLinkedNode
#define _DLinkedNode

template <class T> class DLinkedNode {
	
	protected:

	DLinkedNode<T> * prev;
	DLinkedNode<T> * next;

	T value;

	public:

	DLinkedNode(){
		this->prev = nullptr;
		this->next = nullptr;
	}

	DLinkedNode(T value, DLinkedNode<T> * prev, DLinkedNode<T> * next){
		this->prev = prev;
		this->next = next;
		this->value = value;
	}

	static void destroy(DLinkedNode *n){
		delete n;
	}

	DLinkedNode<T>* getPrev(){
		return this->prev;
	}

	DLinkedNode<T>* getNext(){
		return this->next;
	}

	T getValue(){
		return this->value;
	}

	DLinkedNode<T>* setPrev(DLinkedNode<T> * prev){
		this->prev = prev;
		return this;
	}

	DLinkedNode<T>* setNext(DLinkedNode<T> * next){
		this->next = next;
		return this;
	}

	DLinkedNode<T>* setValue(T value){
		this->value = value;
		return this;
	}
};


#endif