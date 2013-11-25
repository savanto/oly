/*
ID: washirv1
PROG: ariprog
LANG: C++
*/

#include <fstream>
using namespace std;

#define INFILE "ariprog.in"
#define OUTFILE "ariprog.out"

int square(int i) { return i * i; }

int main()
{
	int N, M;
	ifstream fin(INFILE);
	fin >> N >> M;
	fin.close();
	const int NUM = square(M) * 2 + 1;

	// Generate bisquares
	bool bisquares[NUM];
	for (int i = 0; i < NUM; i++)
		bisquares[i] = false;
	for (int p = 0; p <= M; p++)
		for (int q = 0; q <= M; q++)
			bisquares[square(p) + square(q)] = true;

	ofstream fout(OUTFILE);

	// 1 <= b <= 2M^2 / (N - 1)
	bool none = true;
	for (int b = 1, bInc = 1; b <= 2 * square(M) / (N - 1); b += bInc)
	{
		// 0 <= a <= 2M^2 - (N - 1) * b
		for (int a = 0; a <= 2 * square(M) - (N - 1) * b; a++)
		{
			int n = 0;
			while (n < N)
			{
				if (bisquares[a + n * b])
					n++;
				else
					break;
			}
			if (n == N)	// valid sequence found
			{
				if (none)
				{
					bInc = b;
					none = false;
				}
				fout << a << " " << b << endl;
			}
		}
	}

	if (none)
		fout << "NONE" << endl;
	fout.close();

	return 0;
}
