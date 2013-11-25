/*
ID: washirv1
PROG: pprime
LANG: C++
*/

#include <fstream>
using namespace std;

#define INFILE "pprime.in"
#define OUTFILE "pprime.out"

bool prime(int n)
{
	if (n == 2)
		return true;
	if (n % 2 == 0)
		return false;
	for (int i = 3; i * i <= n; i+=2)
		if (n % i == 0)
			return false;
	return true;
}

int main()
{
	ifstream fin(INFILE);
	int a, b, d1, d2, d3, d4, p;
	fin >> a >> b;
	fin.close();

	ofstream fout(OUTFILE);
	// Generate prime palindromes < 100
	for (p = a; p <= 11; p++)
	{
		if (p > b)
			return 0;
		if (prime(p))
			fout << p << endl;
	}
	// Generate prime palindromes < 1000 (3 digits)
	if (a < 1000)
	{
		for (d1 = 1; d1 <= 9; d1+=2)
			for (d2 = 0; d2 <= 9; d2++)
			{
				p = d1 * 101 + d2 * 10;
				if (p < a)
					continue;
				if (p > b)
					return 0;
				if (prime(p))
					fout << p << endl;
			}
	}
	// Generate prime palindromes < 10000 (4 digits)
	if (a < 10000)
	{
		for (d1 = 1; d1 <= 9; d1+=2)
			for (d2 = 0; d2 <= 9; d2++)
			{
				p = d1 * 1001 + d2 * 110;
				if (p < a)
					continue;
				if (p > b)
					return 0;
				if (prime(p))
					fout << p << endl;
			}
	}
	// Generate prime palindromes < 100 000 (5 digits)
	if (a < 100000)
	{
		for (d1 = 1; d1 <= 9; d1+=2)
			for (d2 = 0; d2 <= 9; d2++)
				for (d3 = 0; d3 <= 9; d3++)
				{
					p = d1 * 10001 + d2 * 1010 + d3 * 100;
					if (p < a)
						continue;
					if (p > b)
						return 0;
					if (prime(p))
						fout << p << endl;
				}
	}
	// Generate prime palindromes < 1 000 000 (6 digits)
	if (a < 1000000)
	{
		for (d1 = 1; d1 <= 9; d1+=2)
			for (d2 = 0; d2 <= 9; d2++)
				for (d3 = 0; d3 <= 9; d3++)
				{
					p = d1 * 100001 + d2 * 10010 + d3 * 1100;
					if (p < a)
						continue;
					if (p > b)
						return 0;
					if (prime(p))
						fout << p << endl;
				}
	}
	// Generate prime palindromes < 10 000 000 (7 digits 1234321)
	if (a < 10000000)
	{
		for (d1 = 1; d1 <= 9; d1+=2)
			for (d2 = 0; d2 <= 9; d2++)
				for (d3 = 0; d3 <= 9; d3++)
					for (d4 = 0; d4 <= 9; d4++)
						{
							p = d1 * 1000001 + d2 * 100010 + d3 * 10100 + d4 * 1000;
							if (p < a)
								continue;
							if (p > b)
								return 0;
							if (prime(p))
								fout << p << endl;
						}
	}
	// Generate prime palindromes < 100 000 000 (8 digits 12344321)
	if (a < 100000000)
	{
		for (d1 = 1; d1 <= 9; d1+=2)
			for (d2 = 0; d2 <= 9; d2++)
				for (d3 = 0; d3 <= 9; d3++)
					for (d4 = 0; d4 <= 9; d4++)
						{
							p = d1 * 10000001 + d2 * 1000010 + d3 * 100100 + d4 * 1100;
							if (p < a)
								continue;
							if (p > b)
								return 0;
							if (prime(p))
								fout << p << endl;
						}
	}

	fout.close();
	return 0;
}
