#include <iostream>
#include <string>
#include "biRing.h"

using namespace std;

template<typename Key, typename Info>
biRing<Key, Info>* joinRings(const biRing<Key, Info>& first, const biRing<Key, Info>& second);

string concat(const string& first, const string& second);

int main()
{

	biRing<int, string> test;
	test.insertElement(0, "zero");
	test.insertElement(1, "one");
	test.insertElement(2, "two");
	test.insertElement(3, "three");
	auto it = test.begin();
	int counter = 0;
	do {
		if ((*it) == counter)
		{
			it--;
			counter++;
		}
		else
		{
			cout << "Test Ring was not created" << endl;
			break;
		}
	} while (it != test.end());

	if (counter == 4)
	{
		cout << "Test Ring was created, using insertElement() method" << endl << endl;
	}

	counter = 0;
	int array[4] = { 1,2,6,3 };

	biRing<int, string> snd(test);

	snd.remove(0);

	snd.insertAfter(3, 6, "six");

	it = snd.begin();
	do {
		if ((*it) == array[counter])
		{
			it--;
			counter++;
		}
		else
		{
			cout << "Copy Constructor failed" << endl;
			break;
		}
	} while (it != snd.end());

	if (counter == 4)
	{
		cout << "Second test ring was created using copy constructor," << endl;
		cout << "method remove() and insertAfter() implemented succesfully" << endl << endl;
	}

	int sndArray[5] = { 1,2,5,6,3 };
	counter = 0;

	biRing<int, string> thr;
	thr = snd;
	thr.insertAfter(6, 5, "five");

	it = thr.begin();
	do {
		if ((*it) == sndArray[counter])
		{
			it--;
			counter++;
		}
		else
		{
			cout << "Assignment operator failed" << endl;
			break;
		}
	} while (it != thr.end());

	if (counter == 5)
	{
		cout << "Third test ring was created using assignment operator and method insertAfter()" << endl << endl;
	}

	cout << "ITERATOR TESTS" << endl;

	//ITERATOR TESTS
	int itArray[4] = { 0, 1, 2, 3 };

	biRing<int, string> itTest;

	itTest.insert(itTest.end(), 0, "it zero");
	itTest.insert(itTest.end(), 1, "it one");
	itTest.insert(itTest.end(), 2, "it two");
	itTest.insert(itTest.begin(), 3, "it three");

	counter = 0;
	auto iter = itTest.begin();

	do {
		if ((*iter) == itArray[counter])
		{
			iter--;
			counter++;
		}
		else
		{
			cout << "Creation of fourth testing ring failed" << endl;
			break;
		}
	} while (iter != itTest.end());

	if (counter == 4)
	{
		cout << "Fourth ring was created using Iterator insert()" << endl;
	}


	iter = itTest.find(iter, 2);
	if (*iter == 2)
	{
		cout << "Method find() found designated element" << endl;
	}

	counter = 0;
	itTest.erase(iter);
	iter = itTest.begin();
	do {
		if (*iter == 2)
		{
			cout << "Method erase() did not deleted designated element" << endl;
			break;
		}
		else
		{
			iter++;
			counter++;
		}
	} while (iter != itTest.end());

	if (counter == 3)
	{
		cout << "Method erase() deleted designated element" << endl << endl;;
	}


	cout << "JOINED TEST" << endl;
	biRing<int, string>* joined = NULL;

	int joinedArray[6] = { 3,2,5,6,0,1 };
	cout << "Function uses 3rd Test Ring and 4th Test Ring" << endl;
	counter = 0;
	joined = joinRings(itTest, thr);
	it = joined->begin();
	do {
		if (*it == joinedArray[counter])
		{
			if (*it == 3 || *it == 1)
			{
				if (&it == "it one, one" || &it == "it three, three")
				{
					cout << "Concatenated succesfully" << endl;
				}
				it++;
				counter++;
			}
			else
			{
				it++;
				counter++;
			}
		}
		else
		{
			cout << "joinRings() function failure" << endl;
			break;
		}
	} while (it != joined->end());

	if (counter == 6)
	{
		cout << "Joined Ring was created" << endl;
	}


	joined->print();

	
	cout << "Press any key and enter to close program" << endl;
	getchar();

	return 0;
}

template<typename Key, typename Info>
biRing<Key, Info>* joinRings(const biRing<Key, Info>& first, const biRing<Key, Info>& second)
{
	biRing<Key, Info>* joined = new biRing<Key, Info>;
	if (!first.isEmpty() && !second.isEmpty())
	{
		auto fIt = first.begin();
		auto sIt = second.begin();
		do {
			do {
				if ((*sIt) == (*fIt))
				{
					joined->insertElement((*sIt), concat((&fIt), (&sIt)));
					break;
				}
				sIt++;
			} while (sIt != second.end());
			sIt = second.begin(); 
			fIt++;
		} while (fIt != first.end());
		//reset
		fIt = first.begin();
		sIt = second.begin();
			do {
				joined->insert(joined->end(),(*fIt), (&fIt));//using iterator
				*fIt++;
			} while (fIt != first.end());
			do {
				joined->insert(joined->end(), (*sIt), (&sIt));//using iterator
				sIt++;
			} while (sIt != second.end());
	}
	else
	{
		throw exception();
	}
	return joined;
}

string concat(const string& first, const string& second)
{
	return first + ", " + second;
}
