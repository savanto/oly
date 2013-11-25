/*
ID: washirv1
PROG: palsquare
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

bool isPal(string s)
{
	string r  = "";
	for (int i = s.length() - 1; i >= 0; i--)
		r += s[i];
	return s == r;
}

string digit(int n)
{
	stringstream ss;
	if (n < 10)
		ss << n;
	else
		ss << char(n + 55);
	return ss.str();
}

void convert(int b, int n, string &result)
{
	stringstream ss;
    if (n % b == n)
    {
		result += digit(n);
        return;
    }
	else
	{
		convert(b, n / b, result);
		if (n % b == 0)
			result += digit(0);
		else
			result += digit(n % b);
	}
}

int main()
{
	ofstream fout("palsquare.out");
	ifstream fin("palsquare.in");

	int b;
	fin >> b;

	string rn, rsq;
	for (int n = 1, sq = n * n; n <= 300; n++, sq = n * n)
	{
		rn = "";
		rsq = "";
		convert(b, n, rn);
		convert(b, sq, rsq);
		if (isPal(rsq))
			fout << rn << " " << rsq << endl;
	}

	return 0;
}
