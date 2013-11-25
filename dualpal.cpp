/*
ID: washirv1
PROG: dualpal
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

bool isPal(string s)
{
	for (int f = 0, b = s.length() - 1; f < b; f++, b--)
	{
		if (s[f] != s[b])
			return false;
	}
	return true;
}

void convert(int base, int num, string &result)
{
	stringstream ss;
	if (num < base)
	{
		ss << num;
		result += ss.str();
	}
	else
	{
		convert(base, num / base, result);
		ss << num % base;
		result += ss.str();
	}
}

int main()
{
	ofstream fout("dualpal.out");
	ifstream fin("dualpal.in");

	// read in n and s
	int n, s;
	fin >> n >> s;

	// starting at s, check each number against all bases
	// stopping only when n palindromes have been found
	for (s++; n > 0; s++)
	{
		int p = 0;
		for (int b = 2; p < 2 && b <= 10; b++)
		{
			string r = "";
			convert(b, s, r);
			if (isPal(r))
				p++;
		}
		if (p >= 2)
		{
			fout << s << endl;
			n--;
		}
	}

	return 0;
}
