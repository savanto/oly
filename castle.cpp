/*
ID: washirv1
PROG: castle
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

#define INFILE "castle.in"
#define OUTFILE "castle.out"
typedef vector<vector<int> > Castle;
typedef vector<vector<bool> > Visited;
const int WEST = 1, NORTH = 2, EAST = 4, SOUTH = 8;

int roomSize(const Castle & castle, Visited & visited, int n, int m)
{
	if (n >= castle.size() || n < 0 || m >= castle[n].size() || m < 0 || visited[n][m])
		return 0;
	visited[n][m] = true;
	return 1
		+ (castle[n][m] & WEST  ? 0 : roomSize(castle, visited, n, m-1))
		+ (castle[n][m] & NORTH ? 0 : roomSize(castle, visited, n-1, m))
		+ (castle[n][m] & EAST  ? 0 : roomSize(castle, visited, n, m+1))
		+ (castle[n][m] & SOUTH ? 0 : roomSize(castle, visited, n+1, m));
}

int main()
{
	ifstream fin(INFILE);
	int M, N;
	fin >> M >> N;
//	int castle[N][M];
	Castle castle(N, vector<int>(M));
	int n, m;
	for (n = 0; n < N; ++n)
		for (m = 0; m < M; ++m)
			fin >> castle[n][m];
	fin.close();

	// Find largest room
	vector<int> rooms;
	Visited visited(N, vector<bool>(M, false));
	int max = 0, newMax = 0, maxN = 0, maxM = 0, maxW = 0;
	for (m = 0; m < M; ++m)
	{
		for (n = N-1; n >= 0; --n)
		{
			int size = roomSize(castle, visited, n, m);
			if (size != 0)
				rooms.push_back(size);
			if (size > max)
				max = size;
			// Remove wall, repeat calc
			for (int wall = WEST; wall <= SOUTH; wall <<= 1)
			{
				if (castle[n][m] & wall)
				{
					castle[n][m] &= ~wall;
					Visited v(N, vector<bool>(M, false));
					size = roomSize(castle, v, n, m);
					if (size > newMax)
					{
						newMax = size;
						maxN = n;
						maxM = m;
						maxW = wall;
					}
					castle[n][m] |= wall;
				}
			}
		}
	}
	ofstream fout(OUTFILE);
	fout << rooms.size() << endl;
	fout << max << endl;
	fout << newMax << endl;
	fout << maxN+1 << ' ' << maxM+1 << ' ';
	switch (maxW)
	{
		case WEST:  fout << 'W'; break;
		case NORTH: fout << 'N'; break;
		case EAST:  fout << 'E'; break;
		case SOUTH: fout << 'S'; break;
	}
	fout << endl;

//////////////////////////////////
//
	// Output coords
	cout << "  ";
	for (m = 1; m <= M; ++m)
		cout << "  " << m << " ";
	cout << endl;
	for (n = 0; n < N; ++n)
	{
		// Output North wall
		cout << "  ";
		for (m = 0; m < M; ++m)
			cout << (castle[n][m] & NORTH ? "####" : "#---");
		cout << "#" << endl;
		// Output coords
		cout << n+1 << " ";
		// Output West and East walls
		for (m = 0; m < M; ++m)
			cout << (castle[n][m] & WEST ? "#   " : "|   ");
		cout << "#" << endl;
	}
	// Output South wall
	cout << "  ";
	for (m = 0; m < M; ++m)
		cout << "####";
	cout << "#" << endl;
//
//////////////////////////////////

	fout.close();
	return 0;
}
