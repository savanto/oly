/*
ID: washirv1
PROG: packrec
LANG: C++
*/

#include <vector>
#include <fstream>
using namespace std;

#define INFILE "packrec.in"
#define OUTFILE "packrec.out"

typedef vector<vector<int> > Rects;

int comp(int i)
{
	switch (i)
	{
		case 0:
			return 4;
		case 1:
			return 5;
		case 2:
			return 6;
		case 3:
			return 7;
		case 4:
			return 0;
		case 5:
			return 1;
		case 6:
			return 2;
		case 7:
			return 3;
		default:
			return -1;
	}
}

struct Node
{
	int val;
	Node * next;
	Node(int v, Node * n) : val(v), next(n) {}
};

struct List
{
	Node * first;
	List() : first(NULL) {}
	void insert(int v)
	{
		if (first == NULL)
			first = new Node(v, NULL);
		else if (first->next == NULL)
		{
			if (first->val == v)
				return;
			else if (first->val < v)
				first->next = new Node(v, NULL);
			else
				first = new Node(v, first);
		}
		else
		{
			Node * node = first;
			while (node->next != NULL && node->next->val <= v)
				node = node->next;
			if (node->next == NULL && node->val != v)
				node->next = new Node(v, NULL);
			else if (node->val == v)
				return;
			else
				node->next = new Node(v, node->next);
		}
	}
};

int main()
{
	ifstream fin(INFILE);
	Rects rects = Rects(8, vector<int>(2, 0));
	for (int i = 0; i < 4; i++)
	{
		fin >> rects[i][0] >> rects[i][1];
		rects[i+4][0] = rects[i][1];
		rects[i+4][1] = rects[i][0];
	}
	fin.close();

	// Calculate combos of rectangles, and pack them.
	int a = 10000, x, h, w;
	const int H = 0, W = 1;
	List result;

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (j == i || j == comp(i))
				continue;
			for (int k = 0; k < 8; k++)
			{
				if (k == j || k == comp(j) || k == i || k == comp(i))
					continue;
				for (int l = 0; l < 8; l++)
				{
					if (l == k || l == comp(k) || l == j || l == comp(j) || l == i || l == comp(i))
						continue;
					int r[4] = { i, j, k, l };

					// Packing algorithms
					/* Pack 1
					 * [0][1][2][3]
					 */
					for (x = 0, h = 0, w = 0; x < 4; x++)
					{
						w += rects[r[x]][W];
						if (rects[r[x]][H] > h)
							h = rects[r[x]][H];
					}
					if (h * w <= a)
					{
						if (h * w < a)
						{
							result.first = NULL;
							a = h * w;
						}
						result.insert(h < w ? h : w);
					}

					/* Pack 2
					 * [1][2][3]
					 * [   0   ]
					 */
					for (x = 1, h = 0, w = 0; x < 4; x++)
					{
						w += rects[r[x]][W];
						if (rects[r[x]][H] > h)
							h = rects[r[x]][H];
					}
					if (rects[r[0]][W] > w)
						w = rects[r[0]][W];
					h += rects[r[0]][H];
					if (h * w <= a)
					{
						if (h * w < a)
						{
							result.first = NULL;
							a = h * w;
						}
						result.insert(h < w ? h : w);
					}

					/* Pack 3
					 * [1][2][3]
					 * [  0 ]
					 */
					for (x = 1, h = 0, w = 0; x < 3; x++)
					{
						w += rects[r[x]][W];
						if (rects[r[x]][H] > h)
							h = rects[r[x]][H];
					}
					if (rects[r[0]][W] > w)
						w = rects[r[0]][W];
					w += rects[r[3]][W];
					h += rects[r[0]][H];
					if (rects[r[3]][H] > h)
						h = rects[r[3]][H];
					if (h * w <= a)
					{
						if (h * w < a)
						{
							result.first = NULL;
							a = h * w;
						}
						result.insert(h < w ? h : w);
					}

					/* Pack 4
					 * [1][2][3]
					 * [0]
					 */
					for (x = 2, h = 0, w = 0; x < 4; x++)
					{
						w += rects[r[x]][W];
						if (rects[r[x]][H] > h)
							h = rects[r[x]][H];
					}
					w += (rects[r[0]][W] > rects[r[1]][W] ? rects[r[0]][W] : rects[r[1]][W]);
					if (rects[r[0]][H] + rects[r[1]][H] > h)
						h = rects[r[0]][H] + rects[r[1]][H];
					if (h * w <= a)
					{
						if (h * w < a)
						{
							result.first = NULL;
							a = h * w;
						}
						result.insert(h < w ? h : w);
					}

					/* Pack 5
					 * [1][2][3]
					 *    [0]
					 */
					w = rects[r[1]][W];
					w += rects[r[3]][W];
					w += (rects[r[0]][W] > rects[r[2]][W] ? rects[r[0]][W] : rects[r[2]][W]);
					h = rects[r[1]][H];
					if (rects[r[3]][H] > h)
						h = rects[r[3]][H];
					if (rects[r[2]][H] + rects[r[0]][H] > h)
						h = rects[r[2]][H] + rects[r[0]][H];
					if (h * w <= a)
					{
						if (h * w < a)
						{
							result.first = NULL;
							a = h * w;
						}
						result.insert(h < w ? h : w);
					}

					/* Pack 6
					 * [0][1]
					 * [2][3]
					 */
					w = (rects[r[0]][W] + rects[r[1]][W] > rects[r[2]][W] + rects[r[3]][W] ?
							rects[r[0]][W] + rects[r[1]][W] : rects[r[2]][W] + rects[r[3]][W]);
					h = (rects[r[0]][H] + rects[r[2]][H] > rects[r[1]][H] + rects[r[3]][H] ?
							rects[r[0]][H] + rects[r[2]][H] : rects[r[1]][H] + rects[r[3]][H]);
					// check for overlap
					// if 0[H] < 1[H] && 0[W] < 2[W]
					if ((rects[r[0]][H] < rects[r[1]][H] && rects[r[0]][W] < rects[r[2]][W])
							|| (rects[r[1]][H] < rects[r[0]][H] && rects[r[1]][W] < rects[r[3]][W]))
						continue;
					if (h * w <= a)
					{
						if (h * w < a)
						{
							result.first = NULL;
							a = h * w;
						}
						result.insert(h < w ? h : w);
					}
//					w = (rects[r[0]][W] > rects[r[2]][W] ? rects[r[0]][W] : rects[r[2]][W]) +
//						(rects[r[1]][W] > rects[r[3]][W] ? rects[r[1]][W] : rects[r[3]][W]);
//					h = (rects[r[0]][H] > rects[r[1]][H] ? rects[r[0]][H] : rects[r[1]][H]) +
//						(rects[r[2]][H] > rects[r[3]][H] ? rects[r[2]][H] : rects[r[3]][H]);
//					w = (rects[r[0]][W] + rects[r[1]][W] > rects[r[2]][W] + rects[r[3]][W] ?
//							rects[r[0]][W] + rects[r[1]][W] : rects[r[2]][W] + rects[r[3]][W]);
				}
			}
		}
	}

	// Output results
	ofstream fout(OUTFILE);
	fout << a << endl;
	while (result.first != NULL)
	{
		fout << result.first->val << ' ' << a / result.first->val << endl;
		result.first = result.first->next;
	}
	fout.close();
	return 0;
}
