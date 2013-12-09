/*
ID: washirv1
PROG: lamps
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;

#define INFILE "lamps.in"
#define OUTFILE "lamps.out"

// Toggle all lamps
void button1(int lamps[], int N)
{
	for (int i = 0; i < N; ++i)
		lamps[i] = (lamps[i] + 1) % 2;
}

// Toggle odd lamps
void button2(int lamps[], int N)
{
	for (int i = 0; i < N; i += 2)
		lamps[i] = (lamps[i] + 1) % 2;
}

// Toggle even lamps
void button3(int lamps[], int N)
{
	for (int i = 1; i < N; i += 2)
		lamps[i] = (lamps[i] + 1) % 2;
}

// Toggle every third lamp after the first
void button4(int lamps[], int N)
{
	for (int i = 0; i < N; i += 3)
		lamps[i] = (lamps[i] + 1) % 2;
}

// Check that given lamps configuration is valid against the given FINAL config
bool valid(int lamps[], int FINAL[], int N)
{
	for (int i = 0; i < N; ++i)
		if (FINAL[i] != -1)
			if (FINAL[i] != lamps[i])
				return false;
	return true;
}

void print(int lamps[], int N, ofstream &fout)
{
	for (int i = 0; i < N; ++i)
		fout << lamps[i];
	fout << endl;
}

int main()
{
	ifstream fin(INFILE);
	int N, C;
	fin >> N >> C;
	int FINAL[N], lamps[N], i;
	for (i = 0; i < N; ++i)
	{
		FINAL[i] = -1;	// unknown state lamps
		lamps[i] = 1;	// starting lamps all ON
	}
	fin >> i;
	while (i != -1)		// read in ON lamps
	{
		FINAL[i-1] = 1;
		fin >> i;
	}
	fin >> i;
	while (i != -1)		// read in OFF lamps
	{
		FINAL[i-1] = 0;
		fin >> i;
	}
	fin.close();

	vector<string> results;
	for (int b1 = 0; b1 < 2; ++b1)
	{
		for (int b2 = 0; b2 < 2; ++b2)
		{
			for (int b3 = 0; b3 < 2; ++b3)
			{
				for (int b4 = 0; b4 < 2; ++b4)
				{
					if (valid(lamps, FINAL, N))
					{
						if (b1 + b2 + b3 + b4 <= C && (b1 + b2 + b3 + b4) % 2 == C % 2)
						{
							stringstream ss;
							for (int i = 0; i < N; ++i)
								ss << lamps[i];
							results.push_back(ss.str());
						}
					}
					button4(lamps, N);
				}
				button3(lamps, N);
			}
			button2(lamps, N);
		}
		button1(lamps, N);
	}

	ofstream fout(OUTFILE);
	if (results.size() == 0)
		fout << "IMPOSSIBLE" << endl;
	else
	{
		sort(results.begin(), results.end());
		for (int i = 0; i < results.size(); ++i)
			fout << results[i] << endl;
	}
	fout.close();
	return 0;
}
