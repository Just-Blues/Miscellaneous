#ifndef SLIST_H_INCLUDED
#define SLIST_H_INCLUDED

// Niwiñski Abel (303837)


#include <iostream>
using namespace std;

template <typename Key, typename Info>
struct element// slnode template - it can be def. outside slist
{
	Key key;
	Info info;
	element* next;
};

template <typename Key, typename Info>
class Slist
{
private:

	element<Key, Info> *head;

	Info none = NULL;//this is a workaround exceptions and, to be honest, more work I know this is a terrible practice,
					 //but any idea I tried instead of this didn't work or caused bigger fallout, for details see the 
					 //searchForElement() method implementation
	
	void destructor();// destructor

public:

	Slist();// default ctor
	Slist(Slist& copy);//copy ctr
	~Slist();// destructor
	//REFERENCES!!!!
	void addElementAtTheEnd(const Key key, const Info info); // insert element at the END of the List
	void addElementAtTheBegining(const Key key, const Info info); // insert element at the BEGINING of the List
	bool instertAtPosition(const Key key, const Info info, int pos);// inserts element AFTER the element at the given position, counting from 0 
	//(1st element is on 0. position, 2nd element is on 1st position, so list of size == 5, would have elements from 0th to 4th position)
	void print();// prints list
	bool findElement(const Key& k, int occurance = 1); // checks whether there is an element with this key on the list
	Info& searchForElement(const Key& k, int occurance = 1); // returns the info of the element with given key
	void deleteFirst();// deletes first element //bool?
	void deleteLast();// deletes last element //bool?
	void deleteAtPosition(const Key& pos, int occurance = 1);// deletes chosen element // bool?
	int size();// size - returns number of elements in the slist
	void clear();// clear - removes all elements from the slist
	//void copy(Slist& copy);// method I used to create copy ctr


	//Getters:
	element<Key, Info>* getHead() { return head; }; // gets Head

	Slist& operator=(const Slist& list);
	friend ostream& operator<<(ostream& out, const Slist& slist); // operator<<
};

template <typename Key, typename Info>
Slist<Key, Info>::Slist()
{
	head = NULL;
}

template <typename Key, typename Info>
void Slist<Key, Info>::destructor()
{
	element<Key, Info>* etr = head;
	while (etr)
	{
		etr = etr->next;
		delete head;
		head = etr;
	}
	head = NULL;
}

template <typename Key, typename Info>
Slist<Key, Info>::~Slist()
{
	destructor();
}

template <typename Key, typename Info>
void Slist<Key, Info>::addElementAtTheEnd(const Key key, const Info info)
{
	element<Key, Info> *temp = new element<Key, Info>;
	temp->key = key;
	temp->info = info;
	temp->next = NULL;
	element<Key, Info> *aux = head;
	if (head == NULL)
	{
		head = temp;
		temp = NULL;
	}
	else
	{	
		while (aux)
		{
			if (!aux->next)
			{
				aux->next = temp;
				break;
			}
			aux = aux->next;
		}
	}
}

template <typename Key, typename Info>
void Slist<Key, Info>::addElementAtTheBegining(const Key key, const Info info)
{
	element<Key, Info> *temp = new element<Key, Info>;
	temp->key = key;
	temp->info = info;
	temp->next = NULL;
	if (head == NULL)
	{
		head = temp;
		temp = NULL;
	}
	else
	{
		temp->next = head;
		head = temp;
		temp = NULL;
	}
}

template <typename Key, typename Info>
void Slist<Key, Info>::print()
{
	element<Key, Info> *etr = head;
	cout << "The list" << endl;
	while (etr)
	{
		cout << etr->key << "  " << etr->info << endl;
			etr = etr->next;
	}
}

template <typename Key, typename Info>
bool Slist<Key, Info>::instertAtPosition(const Key key, const Info info, int pos)
{
	int x = 0;
	element<Key, Info> *etr = head;
	if (head == NULL)
	{
		return false;
	}
	else
	{
		while (etr)
		{
			if (x == pos)
			{
				element<Key, Info> *object = new element<Key, Info>;
				object->key = key;
				object->info = info;
				object->next = etr->next;
				etr->next = object;
				return true;
			}
			x++;
			etr = etr->next;
		}
		return false;
	}
	return false;
}

template <typename Key, typename Info>
bool Slist<Key, Info>::findElement(const Key& k, int occurance)
{
	int counter = 0;
	element<Key, Info> *aux = head;
	while (aux)
	{
		if (aux->key == k)
		{
			if (++counter == occurance)
			{
				return true;
			}
		}
		aux = aux->next;
	}
	return false;
}

template <typename Key, typename Info>
Info& Slist<Key, Info>::searchForElement(const Key& k, int occurance)
{
	Info temp = NULL;
	bool check = findElement(k, occurance);
	
	if(check)
	{
		element<Key, Info> *aux = head;
		int counter = 0;
		while (aux)
		{
			if (aux->key == k)
			{
				if (++counter == occurance)
				{
					return aux->info;
				}
			}
			aux = aux->next;
		}
	}	
	else
	{
		cerr << "Not found, did nothing" << endl;
		return none;
	}
	return none;
}

template <typename Key, typename Info>
void Slist<Key, Info>::deleteFirst()
{
	element<Key, Info>* aux = new element<Key, Info>;
	aux = head; 
	head = head->next;
	delete aux;
}

template <typename Key, typename Info>
void Slist<Key, Info>::deleteLast()
{
	element<Key, Info> *curr = new element<Key, Info>;
	element<Key, Info> *prev = new element<Key, Info>;
	curr = head;
	while (curr->next != NULL)
	{
		prev = curr;
		curr = curr->next;
	}
	prev->next = NULL;
	delete curr;
}

template <typename Key, typename Info>
void Slist<Key, Info>::deleteAtPosition(const Key& pos, int occurance)
{
	int counter = 0;
	bool check = findElement(pos, occurance);
	element<Key, Info> *aux = head;
	element<Key, Info> *prev = new element<Key, Info>;
	element<Key, Info> *curr = new element<Key, Info>;
	if (check)
	{
		if (++counter == occurance && aux->key == pos)
		{
			deleteFirst();
		}
		else
		{
			while (aux)
			{
				if (aux->next->next == NULL)
				{
					deleteLast();
					break;
				}
				else
				{
					if (aux->next->key == pos)
					{
						if (++counter == occurance)
						{
							curr = aux;
							prev = curr;
							curr = curr->next;
							prev->next = curr->next;
							break;
						}
					}
				}
				aux = aux->next;
			}
		}
	}
}

template<typename Key, typename Info>
Slist<Key, Info>::Slist(Slist<Key, Info>& copy)
{
	head = NULL;
	element<Key, Info> *xtr = copy.head;
	while (xtr)
	{
		//memoty leak
		//element<Key, Info> *ntr = new element<Key, Info>;
		//ntr->info = xtr->info;
		//ntr->key = xtr->key;
		//ntr->next = NULL;
		addElementAtTheEnd(xtr->key, xtr->info);
		xtr = xtr->next;
	}

}

template<typename Key, typename Info>
Slist<Key, Info>& Slist<Key, Info>::operator=(const Slist<Key, Info>& list)
{
	if (this == &list)
	{
		return *this;
	}
	element<Key, Info> *etr = head;
	while (etr) //remove all elements from *this
	{
		etr = etr->next;
		delete head;
		head = etr;
	}
	element<Key, Info> *xtr = list.head;
	while (xtr)
	{
		element<Key, Info> *ntr = new element<Key, Info>;
		ntr->info = xtr->info;
		ntr->key = xtr->key;
		ntr->next = NULL;
		addElementAtTheEnd(ntr->key, ntr->info);
		xtr = xtr->next;
	}

	return *this;
}


template <typename Key, typename Info>
int Slist<Key, Info>::size()
{
	int counter = 0;
	element<Key, Info> *xtr = head;
	while (xtr)
	{
		counter++;
		xtr = xtr->next;
	}
	return counter;
}

template <typename Key, typename Info>
void Slist<Key, Info>::clear()
{
	element<Key, Info> *etr = head;
	while (etr)
	{
		etr = etr->next;
		delete head;
		head = etr;
	}
	head = NULL;
}


template<typename Key, typename Info>
ostream& operator<<(ostream& out, Slist<Key, Info>& slist)
{
	const element<Key, Info> *etr = slist.getHead();
	out << "The list:" << endl;
	while (etr)
	{
		out << etr->key << "  " << etr->info << endl;
		etr = etr->next;
	}
	return out;
}

#endif // SLIST_H_INCLUDED
