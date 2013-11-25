/*
ID: washirv1
PROG: crypt1
LANG: C++
*/

#include <iostream>
#include <fstream>
using namespace std;

bool validDigit(int x, int d[], int n)
{
	for (int i = 0; i < n; i++)
	{
		if (x == d[i])
			return true;
	}
	return false;
}

bool validSolution(int p[], int d[], int n)
{
	// out of bounds
	if (p[1] > 999 || p[1] < 100)
		return false;
	if (p[2] > 999 || p[2] < 100)
		return false;
	if (p[3] > 9999 || p[3] < 1000)
		return false;
	
	// check digits
	for (int i = 1; i < 4; i++)
	{
		int thou = 0, hund = 0, tens = 0, ones = 0;
		// 4th digit
		if (p[i] >= 1000)
		{
			thou = p[i] / 1000;
			if (! validDigit(thou, d, n))
				return false;
		}
		// 3rd digit
		hund = (p[i] - thou * 1000) / 100;
		if (! validDigit(hund, d, n))
			return false;
		// 2nd digit
		tens = (p[i] - thou * 1000 - hund * 100) / 10;
		if (! validDigit(tens, d, n))
			return false;
		// 1st digit
		ones = (p[i] - thou * 1000 - hund * 100 - tens * 10);
		if (! validDigit(ones, d, n))
			return false;
	}
	return true;
}

int main()
{
	ofstream fout("crypt1.out");
	ifstream fin("crypt1.in");

	int n, i, j, k, q, r, p[4], sol = 0;
	fin >> n;
	int d[n];
	for (i = 0; i < n; i++)
		fin >> d[i];

	// first digit of top
	for (i = 0; i < n; i++)
	{
		// second digit of top
		for (j = 0; j < n; j++)
		{
			// third digit of top
			for (k = 0; k < n; k++)
			{
				// first digit of bot
				for (q = 0; q < n; q++)
				{
					// second digit of bot
					for (r = 0; r < n; r++)
					{
						p[0] = d[i] * 100 + d[j] * 10 + d[k];
						p[1] = d[q] * p[0];
						p[2] = d[r] * p[0];
						p[3] = p[1] + p[2] * 10;
						if (validSolution(p, d, n))
						{
/*							cout << " " << p[0] << endl;
							cout << "x " << d[q] * 10 + d[r] << endl;
							cout << "----" << endl;
							cout << " " << p[2] << endl;
							cout << p[1] << endl;
							cout << "----" << endl;
							cout << p[3] << endl << endl;
*/							sol++;
						}
					}
				}
			}
		}
	}

	fout << sol << endl;

	return 0;
}
