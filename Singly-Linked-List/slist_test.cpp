
// Niwiñski Abel (303837)
/*
	It was all done in Visual Studio environment 
	I tested and compiled it using Code Blocks 17.12, screenshot of compilation result is in the email

	
	I know for sure that this works for int, double, float and char. 
	I would have to implement additional conditions for char* or string, which isn't a problem with my methods, but it would be time-consuming
	
	Due to lack of formal testing I just created the "general main test" which basiclly is a step by step call of methods and functions 
	with additional explanations

*/

#include "slist.h"

template<typename Key, typename Info>
Slist<Key, Info>* join(Slist<Key, Info>& fst, Slist<Key, Info>& snd);

int main()
{
	cout << "Creating 'main' list" << endl;
	Slist<int, double> list;
	list.addElementAtTheEnd(1, 5.5);
	list.addElementAtTheEnd(2, 13.4);
	list.addElementAtTheEnd(14, 2.6);
	list.addElementAtTheBegining(7, 9.2);
	list.addElementAtTheEnd(4, 3.4);
	list.instertAtPosition(5, 1.6, 4);
	list.addElementAtTheBegining(2, 9.9);
	list.print();

	bool temp = list.findElement(2);
	cout <<"Element was found: " << temp << endl;

	temp = list.findElement(20);
	cout << "Element isn't found: " << temp << endl;

	cout << "Info from the FIRST element with key 2 = " << list.searchForElement(2) << endl;
	double modified = list.searchForElement(2,2) += 2.5;
	cout << "Modified SECOND element's info with key 2 = " << modified << endl;
	
	cout << "Current state of list after: (observe the modified element with the key 2)" << endl;
	cout << list;

	Slist<int, double> snd(list); //creating new list snd and copying list
	cout << "Snd copied list: (last sList above this text is list, the one below is snd)" << endl;
	cout << snd;
	cout << "Using snd to test all delete methods" << endl;
	cout << "Before testing delete, the size (will be 7) = " << snd.size() << endl; 
	

	snd.deleteAtPosition(2,2);
	cout << "Deleted SECOND element with key = 2 " << endl;
	cout << snd;

	snd.deleteAtPosition(5);
	cout << "Deleted element with key = 5" << endl;
	cout << snd;

	snd.deleteFirst();
	cout << "Deleted first element" << endl;
	snd.deleteLast();
	cout << "Deleted last element" << endl;

	cout << snd;
		
	snd.clear();
	cout << "Cleared snd ; (snd)" << snd << endl;

	
	Slist<int, double> thr;
	thr.addElementAtTheBegining(7, 2.2);
	thr.addElementAtTheBegining(11, 89.9);
	thr.addElementAtTheBegining(3, 7.7);
	thr.addElementAtTheEnd(5, 6.77);
	cout << "Created new list 'thr' to test activity of join()" << endl;

	cout << "Let me quickly show that operator= works as intended:" << endl;
	Slist<int, double>* test;

	test = &thr;
	cout << "test = &thr, test.print() ";
	test->print();
	cout << endl;

	cout << "A proper show of join(), to quickly recall, two lists that will be used in the test: " << endl;
	cout << "Slist list ; (list) " << list;
	cout << "Slist thr ; (thr) " << thr << endl;

	cout << "Join is called and will show the analysis" << endl;
	test = join(list, thr);
	cout << endl;
	cout << "Joined test list: " << endl;
	test->print();


	int aux; 
		cin >> aux; //I used this to "halt" the program so I could analyze the console output

	return 0;
}

template<typename Key, typename Info>
Slist<Key, Info>* join(Slist<Key, Info>& fst, Slist<Key, Info>& snd)
{
	Slist<Key, Info>* joined = new Slist<Key, Info>;

	element<Key, Info> *ftr = fst.getHead();
	element<Key, Info> *str = snd.getHead();
	while (ftr || str)
	{
		if (ftr == NULL || str == NULL)
		{
			if (ftr)
			{
				while (ftr)
				{
					joined->addElementAtTheEnd(ftr->key, ftr->info);
					ftr = ftr->next;
				}
				break;
			}
			if (str)
			{
				while (str)
				{
					joined->addElementAtTheEnd(str->key, str->info);
					str = str->next;
				}
				break;
			}
			else
			{
				cerr << "Neither ftr nor str exist or they reached the end of the list, check the size of both and compare" << endl;
				break;
			}
		}
		else if (ftr != NULL && str != NULL)
		{
			cout << ftr->key<<" vs "<< str->key << endl;
			if (ftr->key < str->key)
			{
				joined->addElementAtTheEnd(ftr->key, ftr->info);
				ftr = ftr->next;
			}
			else if (str->key < ftr->key)
			{
				joined->addElementAtTheEnd(str->key, str->info);
				str = str->next;
			}
			else if (str->key == ftr->key)
			{
				joined->addElementAtTheEnd(ftr->key, ftr->info);
				ftr = ftr->next;
				joined->addElementAtTheEnd(str->key, str->info);
				str = str->next;
			}
			else
			{
				cerr << "Unforseen condition, check logic" << endl;
				break;
			}
		}
		else
		{
			cerr << "Fatal Error" << endl;
			break;
		}
	}
	return joined;
}
