/*
ID: washirv1
PROG: clocks
LANG: C++
*/

#include <vector>
#include <queue>
#include <fstream>
using namespace std;

#define INFILE "clocks.in"
#define OUTFILE "clocks.out"

typedef vector<vector<int> > Clocks;

struct State
{
	Clocks clocks;
	vector<int> moves;
	State(Clocks c) : clocks(c), moves(vector<int>(0)) {}
	State(Clocks c, vector<int> m) : clocks(c), moves(m) {}
	State(Clocks c, vector<int> m, int s) : clocks(c), moves(m)
	{
		moves.push_back(s);
	}
};

typedef queue<State> States;

short rotate(int i)
{
	return (i + 3) % 12;
}

Clocks doMove(Clocks clocks, int move)
{
	int r, c;
	// A B C
	// D E F
	// G H I
	switch (move)
	{
		case 1:	// ABDE
//			for (r = 0; r < 2; r++)
//				for (c = 0; c < 2; c++)
//					clocks[r][c] = rotate(clocks[r][c]);
			clocks[0][0] = rotate(clocks[0][0]);
			clocks[0][1] = rotate(clocks[0][1]);
			clocks[1][0] = rotate(clocks[1][0]);
			clocks[1][1] = rotate(clocks[1][1]);
			break;
		case 2:	// ABC
//			for (r = 0, c = 0; c < 3; c++)
//				clocks[r][c] = rotate(clocks[r][c]);
			clocks[0][0] = rotate(clocks[0][0]);
			clocks[0][1] = rotate(clocks[0][1]);
			clocks[0][2] = rotate(clocks[0][2]);
			break;
		case 3:	// BCEF
//			for (r = 0; r < 2; r++)
//				for (c = 1; c < 3; c++)
//					clocks[r][c] = rotate(clocks[r][c]);
			clocks[0][1] = rotate(clocks[0][1]);
			clocks[0][2] = rotate(clocks[0][2]);
			clocks[1][1] = rotate(clocks[1][1]);
			clocks[1][2] = rotate(clocks[1][2]);
			break;
		case 4:	// ADG
//			for (r = 0, c = 0; r < 3; r++)
//				clocks[r][c] = rotate(clocks[r][c]);
			clocks[0][0] = rotate(clocks[0][0]);
			clocks[1][0] = rotate(clocks[1][0]);
			clocks[2][0] = rotate(clocks[2][0]);
			break;
		case 5:	// BDEFH
//			for (r = 0, c = 1; r < 3; r++)
//				clocks[r][c] = rotate(clocks[r][c]);
//			for (r = 1, c = 0; c < 3; c += 2)
//				clocks[r][c] = rotate(clocks[r][c]);
			clocks[0][1] = rotate(clocks[0][1]);
			clocks[1][0] = rotate(clocks[1][0]);
			clocks[1][1] = rotate(clocks[1][1]);
			clocks[1][2] = rotate(clocks[1][2]);
			clocks[2][1] = rotate(clocks[2][1]);
			break;
		case 6:	// CFI
//			for (r = 0, c = 2; r < 3; r++)
//				clocks[r][c] = rotate(clocks[r][c]);
			clocks[0][2] = rotate(clocks[0][2]);
			clocks[1][2] = rotate(clocks[1][2]);
			clocks[2][2] = rotate(clocks[2][2]);
			break;
		case 7:	// DEGH
//			for (r = 1; r < 3; r++)
//				for (c = 0; c < 2; c++)
//					clocks[r][c] = rotate(clocks[r][c]);
			clocks[1][0] = rotate(clocks[1][0]);
			clocks[1][1] = rotate(clocks[1][1]);
			clocks[2][0] = rotate(clocks[2][0]);
			clocks[2][1] = rotate(clocks[2][1]);
			break;
		case 8:	// GHI
//			for (r = 2, c = 0; c < 3; c++)
//				clocks[r][c] = rotate(clocks[r][c]);
			clocks[2][0] = rotate(clocks[2][0]);
			clocks[2][1] = rotate(clocks[2][1]);
			clocks[2][2] = rotate(clocks[2][2]);
			break;
		case 9:	// EFHI
//			for (r = 1; r < 3; r++)
//				for (c = 1; c < 3; c++)
//					clocks[r][c] = rotate(clocks[r][c]);
			clocks[1][1] = rotate(clocks[1][1]);
			clocks[1][2] = rotate(clocks[1][2]);
			clocks[2][1] = rotate(clocks[2][1]);
			clocks[2][2] = rotate(clocks[2][2]);
			break;
	}
	return clocks;
}

void enqueueNext(States & states, State & result)
{
	int size = result.moves.size();
	// Each move can be performed only 3 times in a row
	for (int move = (size ? result.moves[size - 1] : 1); move <= 9; move++)
	{
		bool skip = true;
		if (size > 2)	// check that previous 3 moves were not the same as current
		{
			for (int i = size - 1; i >= size - 3; i--)
			{
				if (result.moves[i] != move)
				{
					skip = false;
					break;
				}
			}
		}
		else
			skip = false;
		if (! skip)
			states.push(State(doMove(result.clocks, move), result.moves, move));
	}
}

bool done(const Clocks & clocks)
{
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			if (clocks[i][j])
				return false;
	return true;
}

vector<int> search(States & states)
{
	while (! states.empty())
	{
		if (done(states.front().clocks))
			return states.front().moves;
		enqueueNext(states, states.front());
		states.pop();
	}
}

int main()
{
	int clock, i, j;
	Clocks clocks = Clocks(3, vector<int>(3, 0));
	ifstream fin(INFILE);
	for (i = 0; i < 3; i++)
		for (j = 0; j < 3; j++)
		{
			fin >> clock;
			clocks[i][j] = clock % 12;
		}

	States states;
	states.push(State(clocks));

	vector<int> result = search(states);

	ofstream fout(OUTFILE);
	for (i = 0; i < result.size() - 1; i++)
		fout << result[i] << " ";
	fout << result[i] << endl;
	fout.close();
	return 0;
}
