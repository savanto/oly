/*
ID: washirv1
PROG: knights - EXAMPLE
LANG: C++
*/

#include <fstream>
#include <queue>
#include <vector>
using namespace std;

#define INFILE "knights.in"
#define OUTFILE "knights.out"

typedef vector<vector<short> > Board;
typedef queue<Board> Boards;

int n;

bool isCovered(const Board & knights)
{
	// Each square must have a knight covering it.
	// Two locations in each quadrant, so 8 locations total
	// from which a knight can cover a given square.
	/* . k . k .
	 * k . . . k
	 * . . ? . .
	 * k . . . k
	 * . k . k .
	 */
	int row, col;
	for (int rank = 0; rank < n; rank++)
	{
		for (int file = 0; file < n; file++)
		{
			// Up/left
			row = rank - 2;
			col = file - 1;
			if (row >= 0 && col >= 0)
				if (knights[col][row])
					continue;
			// Left/up
			row = rank - 1;
			col = file - 2;
			if (row >= 0 && col >= 0)
				if (knights[col][row])
					continue;
			// Up/right
			row = rank - 2;
			col = file + 1;
			if (row >= 0 && col < n)
				if (knights[col][row])
					continue;
			// Right/up
			row = rank - 1;
			col = file + 2;
			if (row >= 0 && col < n)
				if (knights[col][row])
					continue;
			// Down/left
			row = rank + 2;
			col = file - 1;
			if (row < n && col >= 0)
				if (knights[col][row])
					continue;
			// Left/down
			row = rank + 1;
			col = file - 2;
			if (row < n && col >= 0)
				if (knights[col][row])
					continue;
			// Down/right
			row = rank + 2;
			col = file + 1;
			if (row < n && col < n)
				if (knights[col][row])
					continue;
			// Right/down
			row = rank + 1;
			col = file + 2;
			if (row < n && col < n)
				if (knights[col][row])
					continue;
			// Not covered
			return false;
		}
	}
	return true;
}

void enqueueNext(Boards & boards, Board & knights)
{
	// Place one additional knight.
	// Try every available space.
	for (int row = 0; row < n; row++)
	{
		for (int col = 0; col < n; col++)
		{
			if (! knights[col][row])
			{
				Board knightsPlusPlus = Board(knights);
				knightsPlusPlus[col][row] = 1;
				boards.push(knightsPlusPlus);
			}
		}
	}
}

Board search(Boards & boards)
{
	while (! boards.empty())
	{
		Board knights = boards.front();
		boards.pop();
		if (isCovered(knights))
			return knights;
		enqueueNext(boards, knights);
	}
	return Board(n, vector<short>(n, 0));
}

int main()
{
	// Read n
	ifstream fin(INFILE);
	fin >> n;
	fin.close();

	Board knights = Board(n, vector<short>(n, 0));
	Boards boards;
	boards.push(knights);

	Board result = search(boards);

	// Output board
	ofstream fout(OUTFILE);
	for (int row = 0; row < n; row++)
	{
		for (int col = 0; col < n; col++)
			if (result[col][row])
				fout << "k" << " ";
			else
				fout << "." << " ";
		fout << endl;
	}
	fout.close();

	return 0;
}
