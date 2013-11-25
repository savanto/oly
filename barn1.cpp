/*
ID: washirv1
PROG: barn1
LANG: C++
*/
#include <fstream>
#include <algorithm>
using namespace std;

int main()
{
	ofstream fout("barn1.out");
	ifstream fin("barn1.in");

	int m, s, c, i, gap, size;
	fin >> m >> s >> c;

	int stall[c];
	for (i = 0; i < c; i++)
		fin >> stall[i];
	sort(stall, stall + c);
	m--;
	while (m)
	{
		for (gap = 0, size = 1, i = 1; i < c; i++)
		{
			if (stall[i] - stall[i-1] > size)
			{
				gap = i;
				size = stall[i] - stall[i-1];
			}
		}
		if (size > 1)
		{
			for (; gap < c; gap++)
				stall[gap] -= (size - 1);
		}
		m--;
	}
	fout << stall[c-1] - stall[0] + 1 << endl;

	return 0;
}
