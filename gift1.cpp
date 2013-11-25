/*
ID: washirv1
PROG: gift1
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

struct NP
{
	string name;
	int give;
	int receive;
	int ng;
	NP() {}
	NP(string s) : name(s), give(0), receive(0), ng(0) {}
};

int main()
{
	ofstream fout("gift1.out");
	ifstream fin("gift1.in");

	// read in number of people
	int np;
	fin >> np;
	NP nps[np];
	// read in each person's name
	string name;
	for (int i = 0; i < np; i++)
	{
		fin >> name;
		nps[i] = NP(name);
	}
	// read in each person and their gift info
	for (int i = 0; i < np; i++)
	{
		fin >> name;
		// find name in nps array
		for (int j = 0; j < np; j++)
		{
			if (name == nps[j].name)
			{
				fin >> nps[j].give >> nps[j].ng;
				// read in recipients
				for (int k = 0; k < nps[j].ng; k++)
				{
					fin >> name;
					for (int m = 0; m < np; m++)
					{
						if (name == nps[m].name)
						{
							if (nps[j].ng)
								nps[m].receive += nps[j].give / nps[j].ng;
							break;
						}
					}
				}
				if (nps[j].ng)
					nps[j].receive += nps[j].give % nps[j].ng;
				break;
			}
		}
	}

	for (int i = 0; i < np; i++)
		fout << nps[i].name << " " << nps[i].receive - nps[i].give << endl;

	return 0;
}
