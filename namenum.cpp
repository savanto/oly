/*
ID: washirv1
PROG: namenum
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
using namespace std;

// return 3-letter sequence based on the given number
string num2letter(char num)
{
	switch (num)
	{
		case '2':
			return "ABC";
			break;
		case '3':
			return "DEF";
			break;
		case '4':
			return "GHI";
			break;
		case '5':
			return "JKL";
			break;
		case '6':
			return "MNO";
			break;
		case '7':
			return "PRS";
			break;
		case '8':
			return "TUV";
			break;
		case '9':
			return "WXY";
			break;
		default:
			return "---";
			break;
	}
}

// recursively binary search for name in dict
bool find(string name, const vector<string> &dict, int start, int end)
{
	int mid = start + (end - start) / 2;
	// base case: down to one entry
	if (start + 1 == end)
	{
		if (dict[mid] == name)
			return true;
		else
			return false;
	}
	// otherwise, divide dict in the middle and search on half
	if (name < dict[mid])
		return find(name, dict, start, mid);
	else
		return find(name, dict, mid, end);
}

// recursively generate the name
void genName(vector<string> &dict, string prefix, string brand, 
		ofstream &fout, bool &found)
{
	// error case
	if (brand.length() < 1)
		return;
	// base case
	if (brand.length() == 1)
	{
		string letter = num2letter(brand[0]);
		for (int i = 0; i < letter.length(); i++)
		{
			if (find(prefix + letter[i], dict, 0, dict.size() - 1))
			{
				fout << prefix + letter[i] << endl;
				found = true;
			}
		}
		return;
	}
	// otherwise
	if (prefix.length() < 1)
		prefix = "";
	string letter = num2letter(brand[0]);
	for (int i = 0; i < letter.length(); i++)
		genName(dict, prefix + letter[i], brand.substr(1, brand.length() - 1), fout, found);
}

int main()
{
	ofstream fout("namenum.out");
	ifstream fin("namenum.in");
	ifstream fdict("dict.txt");

	// read in brand number
	string brand;
	fin >> brand;

	// read in dictionary
	vector<string> dict;
	string s;
	while (fdict.good())
	{
		fdict >> s;
		dict.push_back(s);
	}

	// generate names from brand number
	bool found = false;
	genName(dict, "", brand, fout, found);
	if (! found)
		fout << "NONE" << endl;

	return 0;
}
