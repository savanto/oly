/*
ID: washirv1
PROG: calfflac
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

bool isAlpha(char a)
{
	return ((a >= 65 && a <= 90) || (a >= 97 && a <= 122));
}

bool areEqual(char a, char b)
{
	if (a <= 90)
	{
		if (b <= 90)
			return a == b;
		else
			return a + 32 == b;
	}
	else
	{
		if (b <= 90)
			return a - 32 == b;
		else
			return a == b;
	}
}

int main()
{
	ofstream fout("calfflac.out");
	ifstream fin("calfflac.in");

	string s, maxPal = "";
	getline(fin, s, '\0');
	int center, f, b, length = s.length() - 1, size, maxSize = 0;
//	s = "xmaamy"; length = s.length();
	for (center = 0; center < length; center++)
	{
		//cout << " ";// << endl;//center << endl;
		if (! isAlpha(s[center]))
			continue;
		// case a''a
		f = center;
		b = center - 1;
		for (size = 0; f < length && b >= 0; f++, b--)
		{
			while (! isAlpha(s[f]) && f < length)
				f++;
			while (! isAlpha(s[b]) && b >= 0)
				b--;
			if (areEqual(s[b], s[f]))
				size += 2;
			else
				break;
		}
		if (size > maxSize)
		{
			b++;
			maxPal = s.substr(b, f-b);
			maxSize = size;
//			cout << "a''a " << size << endl;
		}
		// case a'b'a
		f = center + 1;
		b = center - 1;
		for (size = 1; f < length && b >= 0; f++, b--)
		{
			while (! isAlpha(s[f]) && f < length)
				f++;
			while (! isAlpha(s[b]) && b >= 0)
				b--;
			if (areEqual(s[b], s[f]))
				size += 2;
			else
				break;
		}
		if (size > maxSize)
		{
			b++;
			maxPal = s.substr(b, f-b);
			maxSize = size;
//			cout << "a'b'a " << size << endl;
		}
	}
	// strip out surrounding non-alphabetic chars
	f = 0;
	b = maxPal.length() - 1;
	while (! isAlpha(maxPal[f]) && f < maxPal.length())
		f++;
	while (! isAlpha(maxPal[b]) && b >= 0)
		b--;
	maxPal = maxPal.substr(f, b-f+1);
	fout << maxSize << endl << maxPal << endl;
	return 0;
}
