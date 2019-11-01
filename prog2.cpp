//Ben Wabschall
//COSC 2300
//Program 2
//Section 11

#include "timer.h"
#include "WordTree.h"
#include "WordTree.cpp"
#include<iostream>
#include<fstream>
#include<algorithm>
#include<cstring>
#include<vector>

using namespace::std;

string cleanWord(string& word);

int main()
{
	Timer watch;
	vector<string> misspelled;

	WordTree<string> dictionary;
	WordTree<string> book;
	string tmp;

	//counters
	int skipped = 0;

	int itemCount_d = 0;

	int wordsFound = 0;
	int wordsNotFound = 0;

	int compareSuccess = 0;
	int compareFail = 0;

	//error handling for file
	ifstream fileStream_d("dictionary.txt");
	if (!fileStream_d)
	{
		cerr << "Error finding dictionary file." << endl;
		fileStream_d.close();
		fileStream_d.clear();
	}

	//temp variable for words in files
	string dictWord;

	//read in the dictionary
	while (fileStream_d >> dictWord)
	{
		dictionary.callInsert(cleanWord(dictWord));
		itemCount_d++;
		if (itemCount_d == 30000)
		{
			cout << "A quarter of the way.\n" << endl;
		}
		if (itemCount_d == 66000)
		{
			cout << "Halfway\n" << endl;
		}
		if (itemCount_d == 99000)
		{
			cout << "Three quarters.\n" << endl;
		}
		if (itemCount_d == 130000)
		{
			cout << "10k to go.\n" << endl;
		}			
	}
	fileStream_d.close();
	fileStream_d.clear();

	watch.Start();
	ifstream fileStream_b("book.txt");
	if (!fileStream_b)
	{
		cerr << "Error finding file book file." << endl;
		fileStream_b.close();
		fileStream_b.clear();
	}

	string bookWord;
	//read in the book
	while (fileStream_b >> bookWord)
	{
		string cleaned = cleanWord(bookWord);
		if (isalpha(cleaned[0]))
		{
			int comparisons = 0;
			if (dictionary.callFind(cleaned, comparisons))
			{
				compareSuccess = comparisons + compareSuccess;
				wordsFound++;				
			}
			else
			{
				compareFail = comparisons + compareFail;
				wordsNotFound++;
				misspelled.push_back(cleaned);		
			}
		}
		else if (!cleaned.empty())
		{
			skipped++;
		}
	}

	watch.Stop();
	cout << "Dictionary size: " << itemCount_d
		<< "\nDone checking and these are the results: " << endl;
	cout << "Finished in time: " << watch.Time() << endl;
	cout << "There are " << wordsFound << " words found in the dictionary" << endl;
	cout << compareSuccess << " compares. Average: " << (compareSuccess / wordsFound) << endl;
	cout << "There are " << wordsNotFound << " words NOT found in the dictionary" << endl;
	cout << compareFail << " compares. Average: " << (compareFail / wordsNotFound) << endl;
	cout << "There are " << skipped << " words not checked." << endl;

	ifstream("misspelled.txt");
	int msize = misspelled.size();
	for (int i = 0; i < msize; i++)
	{
		cout << misspelled[i] << endl;
	}
	dictionary.~WordTree();
}

string cleanWord(string& word)
{
	transform(word.begin(), word.end(), word.begin(), [] (unsigned char c) {return std::tolower(c);
	string cleaned = "";
	int length = word.length();

	//begin scanning
	for (int i = 0; i <= length; i++)
	{
		//scan for alpha num characters, keep apostrophes
		if (isalnum(word[i]) || word[i] == '\'')
		{
			cleaned += word[i];
		}
	}

	return cleaned;
}
