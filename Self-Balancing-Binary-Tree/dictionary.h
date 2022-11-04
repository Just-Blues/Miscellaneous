#ifndef DICTIONARY_H_INCLUDED
#define DICTIONARY_H_INCLUDED

using namespace std;

template <typename Key, typename Info>
class Dictionary
{
private:
	struct Node
	{
		Node* left;
		Node* right;
		Key key;
		Info info;
		int height;
		int occurance;
		Node(const Key& k, const Info& i, Node *l, Node *r)
		{
			key = k;
			info = i;
			occurance = 1;
			left = l;
			right = r;
			height = 1;
		}
	};

	void inorder(Node* elem);//inorder print
	void preorder(Node* elem);//preorder print
	void postorder(Node* elem);//postoreder print
	void clear(Node* elem);//clear
	void theMostFrequent(Node* elem, int i);//finds the most frequent words
	struct Node* search(Node* whe, const Key k);//search returns adress of node with given key
	Node* insert(Node* whe, const Key& k);//same as insertByKey but uses more efficient methods

	Node* search(const Key k);//calls search()

	int getHeight(Node* whe);//gets the Height of node, efficient
	int getBalance(Node* whe);//gets balance of nodes using getHeight(), efficient
	Node* Left_Rotation(Node* whe);
	Node* Right_Rotation(Node* whe);

	Node* root;
	int siz;


public:
	
	Dictionary();
	~Dictionary();
	void clearCall();//calls clear
	int getSize() { return siz; }

	Info& operator[](const Key k);//uses search(), returns the info about given key, inserts new node if can't find
	int max(int a, int b) { return (a < b) ? b : a; }

	void insert(const Key& k);//sorts alphabetically 
	void auxiliaryPrint(int mode = 1);//uses one of 3 modes of prinitng, 1 - Preorder, 2 - Inorder, 3 - Postorder
	void theMostFrequent(int i);//prints most frequent words that occur more than i times

	bool isEmpty() { if (root == NULL && siz == 0)return true; else return false; }

};

template <typename Key, typename Info>
Dictionary<Key, Info>::Dictionary()
{
	root = NULL;
	siz = 0;
}

template <typename Key, typename Info>
Dictionary<Key, Info>::~Dictionary()
{
	clear(root);
}

template <typename Key, typename Info>
void Dictionary<Key, Info>::clear(Node* elem)
{
	if (elem)
	{
		clear(elem->left);
		clear(elem->right);
		delete elem;
	}
	root = NULL;
	siz = 0;
}

template <typename Key, typename Info>
void Dictionary<Key, Info>::clearCall()
{
	clear(root);
}

template <typename Key, typename Info>
int Dictionary<Key, Info>::getHeight(Node* whe)
{
	if (whe == NULL)
	{
		return 0;
	}
	else
	{
		return whe->height;
	}
}

template <typename Key, typename Info>
int Dictionary<Key, Info>::getBalance(Node* whe)
{
	if (whe == NULL)
	{
		return 0;
	}
	else
	{
		return (getHeight(whe->left) - getHeight(whe->right));
	}
}

template<typename Key, typename Info>
typename Dictionary<Key, Info>::Node* Dictionary<Key, Info>::search(const Key k)
{
	return search(root, k);
}

template<typename Key, typename Info>
typename Dictionary<Key, Info>::Node* Dictionary<Key, Info>::search(Node* whe, const Key k)
{
	if (whe == nullptr)
	{ 
		return nullptr; 
	}
	if (whe->key == k)
	{
		return whe;
	}
	else if (whe->key < k)
	{
		return search(whe->right, k);
	}
	else if (whe->key > k)
	{
		return search(whe->left, k);
	}
}

template <typename Key, typename Info>
typename Dictionary<Key, Info>::Node* Dictionary<Key, Info>::Right_Rotation(Node* whe)
{
	Node*etr =whe->left;
	Node *xtr = etr->right;
	etr->right = whe;
	whe->left = xtr;

	whe->height = max(getHeight(whe->left), getHeight(whe->right)) + 1;
	etr->height = max(getHeight(etr->left), getHeight(etr->right)) + 1;
	return etr;
}

template <typename Key, typename Info>
typename Dictionary<Key, Info>::Node* Dictionary<Key, Info>::Left_Rotation(Node* whe)
{
	Node *etr = whe->right;
	Node *xtr = etr->left;
	etr->left = whe;
	whe->right = xtr;

	whe->height = max(getHeight(whe->left), getHeight(whe->right)) + 1;
	etr->height = max(getHeight(etr->left), getHeight(etr->right)) + 1;
	return etr;
}

template <typename Key, typename Info>
void Dictionary<Key, Info>::theMostFrequent(int i)
{
	Node* aux = root;
	theMostFrequent(aux, i);
}

template <typename Key, typename Info>
void Dictionary<Key, Info>::theMostFrequent(Node* whe, int i)
{
	if (whe == NULL)
	{
		return;
	}
	if (whe != NULL && whe->occurance > i && whe->key.length() > 3 )
	{
		cout << whe->info << " " << whe->key << " Occurs: " << whe->occurance << endl;
	}
	theMostFrequent(whe->left, i);
	theMostFrequent(whe->right, i);
}

template<typename Key, typename Info>
Info& Dictionary<Key, Info>::operator[](const Key k)
{
	if (search(root, k) == nullptr)
	{
		cout << "Operator[] didn't find node with given key, creating new Node" << endl;
		insert(k);
	}
	Node* aux = search(root, k);
	return aux->info;
}

template <typename Key, typename Info>
void Dictionary<Key, Info>::insert(const Key& k)
{
	root = insert(root, k);
}

template <typename Key, typename Info>
typename Dictionary<Key, Info>::Node* Dictionary<Key, Info>::insert(Node* whe, const Key& k)
{
	if (whe == NULL)
	{
		whe = new Node(k, 0, NULL, NULL);
		siz++;
		return whe;
	}

	if (k < whe->key)
	{
		whe->left = insert(whe->left, k);
		//whe = balance(whe); //no height calculation
	}
	else if (k > whe->key)
	{
		whe->right = insert(whe->right, k);
		//whe = balance(whe); //no height calculation 
	}
	else
	{
		whe->occurance++;
		return whe;
	}

	
	whe->height = 1 + max(getHeight(whe->left), getHeight(whe->right));

	int balance = getBalance(whe);
	if (balance > 1 && k < whe->left->key)
	{
		return Right_Rotation(whe);
	}
	if (balance < -1 && k > whe->right->key)
	{
		return Left_Rotation(whe);
	}
	if (balance > 1 && k > whe->left->key)
	{
		whe->left = Left_Rotation(whe->left);
		return Right_Rotation(whe);
	}
	if (balance < -1 && k < whe->right->key)
	{
		whe->right = Right_Rotation(whe->right);
		return Left_Rotation(whe);
	}
	return whe; 
}

template<typename Key, typename Info>
void Dictionary<Key, Info> ::auxiliaryPrint(int mode)
{
	switch (mode)
	{
	case 1:
		cout << "Preorder Traversal:" << endl;
		preorder(root);
		break;
	case 2:
		cout << "Inorder Traversal:" << endl;
		inorder(root);
		break;
	case 3:
		cout << "Postorder Traversal:" << endl;
		postorder(root);
		break;
	default:
		break;
	}
}

template<typename Key, typename Info>
void Dictionary<Key, Info>::inorder(Node* elem)
{
	if (elem == NULL)
	{
		return;
	}
	inorder(elem->left);
	cout << elem->key << " " << elem->info << " Occurs: " << elem->occurance << endl;
	inorder(elem->right);
}

template<typename Key, typename Info>
void Dictionary<Key, Info>::preorder(Node* elem)
{
	if (elem == NULL)
	{
		return;
	}	
	cout << elem->key << " " << elem->info << " Occurs: " << elem->occurance << endl;
	preorder(elem->left);
	preorder(elem->right);
}

template<typename Key, typename Info>
void Dictionary<Key, Info>::postorder(Node* elem)
{
	if (elem == NULL)
	{
		return;
	}
	postorder(elem->left);
	postorder(elem->right);		
	cout << elem->key << " " << elem->info << " Occurs: " << elem->occurance << endl;
}




#endif