/*
ID: washirv1
PROG: milk2
LANG: C++
*/
#include <iostream>
#include <fstream>

using namespace std;

int main()
{
	ofstream fout("milk2.out");
	ifstream fin("milk2.in");

	// read in farmer info and find overall start and end times
	const int RANGE = 1000000;
	int n;
	fin >> n;
	int starts[n];
	int ends[n];
	int start = RANGE, end = 0;
	for (int i = 0; i < n; i++)
	{
		fin >> starts[i] >> ends[i];
		if (starts[i] < start)
			start = starts[i];
		if (ends[i] > end)
			end = ends[i];
	}

	// create timeline and fill based on farmer info
	int time[RANGE] = { 0 };
	for (int i = 0; i < n; i++)
	{
		for (int j = starts[i]; j < ends[i]; j++)
			time[j]++;
	}

	// traverse timeline and look for periods of milking and idleness
	int milk = 0, idle = 0, maxMilk = 0, maxIdle = 0;
	for (int i = start; i < end; i++)
	{
		if (time[i])	// milking
		{
			if (maxIdle < idle)
				maxIdle = idle;
			milk++;
			idle = 0;
		}
		else			// idle
		{
			if (maxMilk < milk)
				maxMilk = milk;
			idle++;
			milk = 0;
		}
	}

	if (maxIdle < idle)
		maxIdle = idle;
	if (maxMilk < milk)
		maxMilk = milk;

	fout << maxMilk << ' ' << maxIdle<< endl;

	return 0;
}
