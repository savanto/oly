/*
ID: washirv1
PROG: checker
LANG: C++
*/

#include <fstream>
using namespace std;

#define INFILE "checker.in"
#define OUTFILE "checker.out"

#define ROW_MASK 0xFFFF0000
#define COL_MASK 0x0000FFFF
#define ROW1     0x00000001
#define COL1     0x00010000
#define DIAG1	 0x0000000000000001
#define DIAG2	 0x0000000100000000
#define MAX_RES  0xFFFFFFFFFFFFFFFF
void search(int row, int board[], long long int diags, unsigned long long int sols[], unsigned int & nsols, const int N)
{
	// Board is complete
	if (row == -1)
	{
		int j, k, bit;
		unsigned long long int sol = 0;
		for (int i = 0; i < N; ++i)
		{
			for (bit = board[i] & COL_MASK, j = 0; bit > 0; bit >>= 1, ++j);
			sol = sol * 16 + j;
		}
		if (sol < sols[0])
		{
			sols[2] = sols[1];
			sols[1] = sols[0];
			sols[0] = sol;
		}
		else if (sol < sols[1])
		{
			sols[2] = sols[1];
			sols[1] = sol;
		}
		else if (sol < sols[2])
			sols[2] = sol;
		++nsols;
		return;
	}
	// Place queen in given row
	for (int col = 0; col < N; ++col)
	{
		// Check for conflicts
		if (
				   ! (board[col] & COL_MASK)
				&& ! (diags & (DIAG1 << (row + col))) 
				&& ! (diags & (DIAG2 << (row + (N-1 - col))))
		)
		{
			// Flip bit to set queen
			board[row] ^= (COL1 << col);
			board[col] ^= (ROW1 << row);
			diags ^= (DIAG1 << (row + col)) | (DIAG2 << (row + (N-1 - col)));
			// Search new board
			search(row - 1, board, diags, sols, nsols, N);
			// Flip bit to unset queen;
			board[row] ^= (COL1 << col);
			board[col] ^= (ROW1 << row);
			diags ^= (DIAG1 << (row + col)) | (DIAG2 << (row + (N-1 - col)));
		}
	}
}

inline void print(ofstream & fout, unsigned long long int res, const int N)
{
	int sol[N], i, rem;
	for (i = N-1; i >= 0; --i)
	{
		rem = res % 16;
		sol[i] = rem;
		res /= 16;
	}
	fout << sol[0];
	for (i = 1; i < N; ++i)
		fout << ' ' << sol[i];
	fout << endl;
}

int main()
{
	int N;
	ifstream fin(INFILE);
	fin >> N;
	fin.close();

	unsigned int nsols = 0;
	unsigned long long int sols[3] = { MAX_RES };
	long long int diags = 0;
	int board[N];
	for (int i = 0; i < N; ++i)
		board[i] = 0;
	search(N-1, board, diags, sols, nsols, N);

	ofstream fout(OUTFILE);
	for (int i = 0; i < 3; ++i)
		print(fout, sols[i], N);
	fout << nsols << endl;
	fout.close();

	return 0;
}
