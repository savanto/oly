/*
ID: washirv1
PROG: queens - EXAMPLE
LANG: C++
*/

#include <fstream>
#include <vector>

using namespace std;

#define INFILE "queens.in"
#define OUTFILE "queens.out"

typedef vector<vector<short> > Board;
int n;

bool isAttacked(const Board & queens, int rank, int file)
{
	int row, col;
	// Check row
	for (row = 0; row < n; row++)
		if (queens[file][row])
			return true;
	// Check col
	for (col = 0; col < n; col++)
		if (queens[col][rank])
			return true;
	// Check diags
	row = rank;
	col = file;
	while (row >= 0 && col >= 0)
		if (queens[col--][row--])
			return true;
	row = rank;
	col = file;
	while (row < n && col < n)
		if (queens[col++][row++])
			return true;
	row = rank;
	col = file;
	while (row < n && col >= 0)
		if (queens[col--][row++])
			return true;
	row = rank;
	col = file;
	while (row >= 0 && col < n)
		if (queens[col++][row--])
			return true;
	return false;
}

bool search(Board & queens, int col)
{
	// If all cols have a queen, done.
	if (col >= n)
		return true;

	// For each row, attempt to place a queen.
	for (int row = 0; row < n; row++)
	{
		if (! isAttacked(queens, row, col))
		{
			queens[col][row] = 1;
			if (search(queens, col + 1))
				return true;
			else
				queens[col][row] = 0;
		}
	}
	return false;
}

int main()
{
	// Read in n
	ifstream fin(INFILE);
	fin >> n;
	fin.close();

	Board queens = Board(n, vector<short>(n, 0));

	search(queens, 0);

	// Output board
	ofstream fout(OUTFILE);
	for (int row = 0; row < n; row++)
	{
		for (int col = 0; col < n; col++)
			if (queens[col][row])
				fout << "Q" << " ";
			else
				fout << "." << " ";
		fout << endl;
	}
	fout.close();

	return 0;
}
