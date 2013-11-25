/*
ID: washirv1
PROG: friday
LANG: C++
*/
#include <iostream>
#include <fstream>

using namespace std;

int main()
{
	ofstream fout("friday.out");
	ifstream fin("friday.in");

	int N;
	fin >> N;

	// S S M T W T F
	int week[7] = { 0 };
	int w = 2;	// initial start is on Mon, Jan 1, 1900

	// J F M A M J J A S O N D
	int months[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	int m = 0;
	const int FEB = 1;
	for (int year = 1900; year < 1900 + N; year++)
	{
		// calculate if this year is a leap year
		if (year % 100 == 0)
		{
			if (year % 400 == 0)
				months[FEB] = 29;
		}
		else
		{
			if (year % 4 == 0)
				months[FEB] = 29;
		}
		// iterate over the months in the year
		for (int m = 0; m < 12; m++)
		{
			// iterate over the days in the month
			for (int day = 1; day <= months[m]; day++)
			{
				if (w >= 7)
					w = 0; // reset the week index
				if (day == 13)
					week[w]++;
				w++;
			}
		}

		months[FEB] = 28; // reset leap year
	}

	// output week array
	for (int i = 0; i < 7; i++)
	{
		fout << week[i];
		if (i < 6)
			fout << " ";
	}
	fout << endl;
	return 0;
}
