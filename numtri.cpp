/*
ID: washirv1
PROG: numtri
LANG: C++
*/

#include <fstream>
using namespace std;

#define INFILE "numtri.in"
#define OUTFILE "numtri.out"

/* attempt at recursive solution
typedef vector<vector<int> > Triangle;
int sum(const Triangle & tri, int row, int col)
{
	if (row == tri.size() - 2)
		return tri[row][col] + (tri[row+1][col] > tri[row+1][col+1] ? tri[row+1][col] : tri[row+1][col+1]);
	int leftTriangle = tri[row][col] + sum(tri, row + 1, col);
	int rightTriangle = tri[row][col] + sum(tri, row + 1, col + 1);
	return (leftTriangle > rightTriangle ? leftTriangle : rightTriangle);
}
*/

int main()
{
	ifstream fin(INFILE);
	int n, i, j;
	fin >> n;
	int tri[n][n];

	for (i = 0; i < n; i++)
		for (j = 0; j <= i; j++)
			fin >> tri[i][j];
	fin.close();

	for (i = n - 2; i >= 0; i--)
		for (j = 0; j <= i; j++)
			tri[i][j] = tri[i][j] + (tri[i+1][j] > tri[i+1][j+1] ? tri[i+1][j] : tri[i+1][j+1]);

	ofstream fout(OUTFILE);
	fout << tri[0][0] << endl;
	fout.close();

	return 0;
}
