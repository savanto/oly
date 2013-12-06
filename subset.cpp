/*
ID: washirv1
PROG: subset
LANG: C++
*/

#include <iostream>
#include <fstream>
using namespace std;

#define INFILE "subset.in"
#define OUTFILE "subset.out"

void subsets(int p[], int P, int s[], int S)
{
	if (S == 0)
	{
		if (P == 0)
		{
			cout << "  null" << endl << '}' << endl;
			return;
		}
		cout << "  { ";
		for (int i = 0; i < P; i++)
			cout << p[i] << ' ';
		cout << '}' << endl;
		return;
	}
	int j, q[P+1], t[S-1];
	for (j = 0; j < P; j++)
		q[j] = p[j];
	q[P] = s[0];
	for (j = 1; j < S; j++)
		t[j-1] = s[j];
	subsets(q, P + 1, t, S - 1);
	subsets(p, P, t, S - 1);
}

int main()
{
	ifstream fin(INFILE);
	int N;
	fin >> N;
	fin.close();

	int n[N], P = 0, p[P];
	for (int i = 1; i <= N; i++)
		n[i-1] = i;
	cout << '{' << endl;
	subsets(p, P, s, S);

	ofstream fout(OUTFILE);

	fout.close();
	return 0;
}
