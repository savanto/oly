/*
ID: washirv1
PROG: transform
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

// rotate given pattern 90 degrees clockwise
vector<string> rotate(const vector<string> &patt)
{
	string line;
	vector<string> tran;
	for (int i = 0; i < patt.size(); i++)
	{
		line = "";
		for (int j = patt.size() - 1; j >= 0; j--)
			line += patt[j][i];
		tran.push_back(line);
	}
	return tran;
}

// reflect given pattern horizontally
vector<string> reflect(const vector<string> &patt)
{
	string line;
	vector<string> tran;
	for (int i = 0; i < patt.size(); i++)
	{
		line = "";
		for (int j = patt.size() - 1; j >= 0; j--)
			line += patt[i][j];
		tran.push_back(line);
	}
	return tran;
}

// check if two given patterns are equal
bool equal(const vector<string> &patt1, const vector<string> &patt2)
{
	for (int i = 0; i < patt1.size(); i++)
	{
		for (int j = 0; j < patt1.size(); j++)
		{
			if (patt1[i][j] != patt2[i][j])
				return false;
		}
	}
	return true;
}

int main()
{
	ofstream fout("transform.out");
	ifstream fin("transform.in");

	int n;
	fin >> n;
	// read in pattern
	vector<string> patt = vector<string>(n);
	for (int i = 0; i < n; i++)
		fin >> patt[i];
	// read in transformed pattern
	vector<string> tran = vector<string>(n);
	for (int i = 0; i < n; i++)
		fin >> tran[i];

	// check transformations
	vector<string> refl = reflect(patt);
	for (int i = 1; i <= 3; i++)	// rotate 3 times and check
	{
		patt = rotate(patt);
		if (equal(patt, tran))	// #1,2,3 90,180,270 deg rotation
		{
			fout << i << endl;
			return 0;
		}
	}
	if (equal(refl, tran))	// #4 check if pattern is reflected
	{
		fout << 4 << endl;
		return 0;
	}
	for (int i = 1; i <= 3; i++)	// rotate 3 times and check
	{
		refl = rotate(refl);
		if (equal(refl, tran))	// #5 combination of reflection and rotation
		{
			fout << 5 << endl;
			return 0;
		}
	}
	patt = rotate(patt);	// one more rotation to get back original
	if (equal(patt, tran))	// #6 check if patterns already equal
	{
		fout << 6 << endl;
		return 0;
	}

	fout << 7 << endl;		// #7 no transformation can create tran

	return 0;
}
