#ifndef BIRING_H_INCLUDED
#define BIRING_H_INCLUDED


using namespace std;


template <typename Key, typename Info>
class biRing
{
	struct Node
	{
		Key key;
		Info info;
		Node* next;
		Node* prev;
		Node(Key k, Info i, Node* n, Node* p)
		{
			key = k;
			info = i;
			next = n;
			prev = p;
		}
	};

	Node* any;

	bool isThereOnlyOneElement();
	bool exist(Key key);

public:

	biRing();
	biRing(const biRing& copy);
	~biRing();
	bool isEmpty() const { if (any == NULL) { return true; } return false; };
	void clear();
	void insertElement(Key key, Info info);//insterts AFTER any
	void insertAfter(const Key& where, Key key, Info info);//inserts AFTER where
	void remove(Key key);
	void print();
	biRing& operator=(const biRing& ring);


	friend ostream& operator<<(ostream& os, const biRing& ring)
	{
		struct Node* etr = ring.any;
		os << "The list by previous" << endl;
		do
		{
			os << etr->key << "  " << etr->info << endl;
			etr = etr->prev;
		} while (etr != ring.any);

		return os;
	};


	//ITERATOR BELOW


	class Iterator
	{
	private:
		friend class biRing<Key, Info>;
		Node* nodePtr;
		Iterator(Node* s) : nodePtr(s) {};
	public:
		Iterator() : nodePtr(nullptr) {};

		bool operator!=(const Iterator& itr) const
		{
			return nodePtr != itr.nodePtr;
		}

		Key& operator*() const
		{
			return nodePtr->key;
		}

		Info& operator&() const
		{
			return nodePtr->info;
		}

		Iterator& operator++()
		{
			if(nodePtr)
			nodePtr = nodePtr->next;
			return *this;
		}

		Iterator& operator--()
		{
			if (nodePtr)
				nodePtr = nodePtr->prev;
			return *this;
		}

		Iterator operator++(int)
		{
			Iterator temp = *this;
			++*this;
			return temp;
		}

		Iterator operator--(int)
		{
			Iterator temp = *this;
			--*this;
			return temp;
		}

		Iterator& operator=(Node* aux)
		{
			this->nodePtr = aux;
			return *this;
		}

	};
	Iterator begin() const
	{
		return Iterator(any);
	}

	Iterator end() const
	{
		return Iterator(any);
	}

	Iterator insert(Iterator pos, const Key& key, const Info& info)
	{
		if (isEmpty())
		{
			Node* aux = new Node(key, info, NULL, NULL);
			any = aux;
			return pos;
		}
		else if (isThereOnlyOneElement())
		{
			Node* aux = new Node(key, info, any, any);
			any->next = aux;
			any->prev = aux;
			return pos;
		}
		else if (!exist(key))
		{
			Node* aux = new Node(key, info, pos.nodePtr->next, pos.nodePtr);
			pos.nodePtr->next->prev = aux;
			pos.nodePtr->next = aux;
			return pos;
		}
		else
		{
			return pos;
		}
	}

	Iterator erase(Iterator pos)
	{
		if (isThereOnlyOneElement())
		{
			delete any;
			return pos;
		}
		else if (!isEmpty())
		{
			Node* aux = pos.nodePtr;
			aux->next->prev = aux->prev;
			aux->prev->next = aux->next;
			if (aux == any)
			{
				any = any->prev;
			}
			delete aux;
			return pos;
		}
		return pos;
	}

	Iterator find(Iterator pos, const Key& key)
	{
		if (exist(key))
		{
			do {
				if ((*pos) == key)
				{
					return pos;
				}
				pos++;
			} while (pos != this->end());
		}
		else
		{
			cout << "No element with this key" << endl;
			return pos;
		}
		return pos;
	}

};

template<typename Key, typename Info>
biRing<Key,Info>::biRing()
{
	any = NULL;
}

template<typename Key, typename Info>
biRing<Key, Info>::~biRing()
{
	clear();
	delete any;
}

template<typename Key, typename Info>
biRing<Key, Info>::biRing(const biRing<Key, Info>& copy)
{
	any = NULL;
	Node* ctr = copy.any;
	do {
		insertElement(ctr->key, ctr->info);
		ctr = ctr->prev;
	} while (ctr != copy.any);
}

template<typename Key, typename Info>
void biRing<Key, Info>::clear()
{
	if (isEmpty())
	{
		cout << "No elements :: Message called by clear()" << endl;
	}
	else if (isThereOnlyOneElement())
	{
		delete any;
	}
	else
	{
		while (any->next != any)
		{
			Node* aux = any->next;
			aux->next->prev = any;
			any->next = aux->next;
			delete aux;
		}
		delete any;
	}
	any = NULL;
}

template<typename Key, typename Info>
void biRing<Key, Info>::remove(Key key)
{
	if (exist(key))
	{
		if (isThereOnlyOneElement())
		{
			delete any;
		}
		else
		{
			Node* rtr = any;
			while (rtr->key != key)
			{
				rtr = rtr->next;
			}
			if (rtr == any)
			{
				rtr->next->prev = rtr->prev;
				rtr->prev->next = rtr->next;
				any = rtr->prev;
				delete rtr;
			}
			else
			{
				rtr->next->prev = rtr->prev;
				rtr->prev->next = rtr->next;
				delete rtr;
			}
		}
	}
	else
	{
		cout << "No such element" << endl;
	}
}

template<typename Key, typename Info>
void biRing<Key, Info>::insertElement(Key key, Info info)//after any
{
	if (isEmpty())
	{
		Node* aux = new Node(key, info, NULL, NULL);
		any = aux;
	}
	else if (isThereOnlyOneElement() && any->key != key)
	{
		Node* aux = new Node(key, info, any, any);
		any->next = aux;
		any->prev = aux;
	}
	else if (!exist(key))
	{
		Node* aux = new Node(key, info, any->next, any);
		any->next->prev = aux;
		any->next = aux;
	}
}

template<typename Key, typename Info>
void biRing<Key, Info>::insertAfter(const Key& where, Key key, Info info)
{
	if (!isEmpty())
	{
		if (exist(where) && !exist(key))
		{
			Node* aux = any;
			while (aux->key != where)
			{
				aux = aux->next;
			}
			Node* add = new Node(key, info, aux->next, aux);
			aux->next->prev = add;
			aux->next = add;
		}
		else
		{
			cout << "No such element or you must change the key of new element" << endl;
		}
	}
	else
	{
		insertElement(key, info);
	}
}

template<typename Key, typename Info>
void biRing<Key, Info>::print()
{
	Node* aux = any;
	do
	{
		cout << aux->key << "  " << aux->info << endl;
		aux = aux->next;
	} while (aux != any );
}

template<typename Key, typename Info>
bool biRing<Key, Info>::isThereOnlyOneElement()
{
	if (!isEmpty() && any->next == NULL && any->prev == NULL)
	{
		return true;
	}
	return false;
}

template<typename Key, typename Info>
bool biRing<Key, Info>::exist(Key key)
{
	Node* aux = any;
	do
	{
		if (aux->key == key)
		{
			return true;
		}
		aux = aux->next;
	} while (aux != any);

	return false;
}

template<typename Key, typename Info>
biRing<Key, Info>& biRing<Key, Info>::operator=(const biRing<Key, Info>& ring)
{
	if (this == &ring)
	{
		return *this;
	}
	clear();
	Node* etr = ring.any;
	do 	{
		insertElement(etr->key, etr->info);
		etr = etr->prev;
	} while (etr != ring.any);
	
	return *this;
}


#endif // BIRING_H_INCLUDED
