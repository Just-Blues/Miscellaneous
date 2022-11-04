#include <chrono>
#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include "dictionary.h"
using namespace std;
using namespace std::chrono;

int main()
{

	string str;
	Dictionary<string, int> avl;
	avl.insert("eleven");
	avl.insert("twelve");
	avl.insert("fourteen");
	avl.insert("fifteen");
	avl.insert("thirteen");
	avl.insert("seven");
	avl.insert("eight");
	avl.insert("one");
	avl.insert("two");
	avl.insert("twenty");
	avl.insert("six");
	avl.insert("three");

	avl.insert("eleven");
	avl.insert("twelve");
	avl.insert("fourteen");
	avl.insert("fifteen");
	avl.insert("two");
	avl.insert("twenty");
	avl.insert("six");
	avl.insert("three");

	cout << "The order of inorder sort: " << endl;
	cout << "eight, eleven, fifteen, fourteen, one, seven, six, thirteen, three, twelve, twenty, two" << endl << endl;
	avl.auxiliaryPrint(2);
	cout << endl;

	cout << "Calling operator[six]" << endl;
	if (avl["six"] == 1)
	{
		avl["six"] += 5;
		cout << "Found 'six' and changed its info to 6" << endl;
	}

	cout << "Calling operator[nine]" << endl;
	if (avl["nine"] == 0)
	{
		cout << "Found 'nine' after inserting" << endl << endl;
	}

	avl.auxiliaryPrint(2);
	cout << endl;

	avl.clearCall();
	if (avl.isEmpty())
	{
		cout << "Cleared basic test avl" << endl << endl;
	}

	cout << "TheVoyageofBeagle.txt" << endl;

	high_resolution_clock::time_point start = high_resolution_clock::now();

	Dictionary<string, int> Dictionary;
	fstream file;
	string word, filename;

	filename = "TheVoyageofBeagle.txt";

	file.open(filename.c_str());

	ifstream is(filename);
	if (!is.good())
	{
		cout << "Cannot open input file: " << filename << endl;
		return -1;
	}
	while (file >> word)
	{
		Dictionary.insert(word);
	}

	high_resolution_clock::time_point now = high_resolution_clock::now();
	duration<double> time_span = duration_cast<duration<double>>(now - start);

	cout << "Counting in " << time_span.count() << " seconds." << endl;
	cout << Dictionary.getSize() << " unique words found." << endl;

	int a = 600;

	cout << "Printing most frequent words that occur at least "<< a <<" times and have more than 3 letters" << endl;
	Dictionary.theMostFrequent(a);

	cout << "Called operator[rhinoceroses]" << endl;
	cout << "Number of times rhinoceroses occur in the text: "<< Dictionary["rhinoceroses"] << endl;
	cout << "Called search(season)" << endl;
	//Dictionary.auxiliaryPrint();
	Dictionary.clearCall();
	if (Dictionary.isEmpty())
	{
		cout << "Cleared Dictionary" << endl;
	}
	file.close();


	cout << "Program ended all it's tasks/test, getchar() was used to halt the program, press any key and enter" << endl;
	getchar();

	return 0;
}