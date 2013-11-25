/*
ID: washirv1
PROG: ride
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
	ofstream fout("ride.out");
	ifstream fin("ride.in");

	string comet, group;
	fin >> comet >> group;
	long unsigned int cometSum = 1, groupSum = 1;
	for (int i = 0; i < comet.length(); i++)
		cometSum *= (int)comet[i] - 64;
	for (int i = 0; i < group.length(); i++)
		groupSum *= (int)group[i] - 64;

	if (cometSum % 47 == groupSum % 47)
		fout << "GO" << endl;
	else
		fout << "STAY" << endl;

	return 0;
}
