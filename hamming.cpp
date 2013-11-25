/*
ID: washirv1
PROG: hamming
LANG: C++
*/

#include <fstream>
using namespace std;

#define INFILE "hamming.in"
#define OUTFILE "hamming.out"

bool hamming(int hams[], int n, int d, int test)
{
	for (int i = 0; i < n; ++i)
	{
		int bits = 0, j = hams[i] ^ test;
		while (j > 0)
		{
			j &= (j - 1);
			++bits;
		}
		if (bits < d)
			return false;
	}
	return true;
}

int main()
{
	ifstream fin(INFILE);
	int N, B, D;
	fin >> N >> B >> D;
	fin.close();

	ofstream fout(OUTFILE);
	int ham[N];
	ham[0] = 0;
	fout << 0;
	for (int i = 1, nl = 1; i < N; ++i, ++nl)
	{
		int j;
		for (j = ham[i-1] + 1; ! hamming(ham, i, D, j); ++j);
		ham[i] = j;
		if (nl % 10 == 0)
			fout << endl << j;
		else
			fout << ' ' << j;
	}
	fout << endl;
	fout.close();
	return 0;
}
