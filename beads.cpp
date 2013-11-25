/*
ID: washirv1
PROG: beads
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Bead
{
    char color;
    Bead *next;
    Bead *prev;
    Bead() : color(0), next(NULL), prev(NULL) {}
    Bead(char c) : color(c), next(NULL), prev(NULL) {}
};  

int main()
{
    ofstream fout("beads.out");
    ifstream fin("beads.in");

	// read in necklace length and sequence
    int n;
    string input;
    fin >> n >> input;

	// store necklace in circular double-linked list
    Bead *start = new Bead(input[0]);
    Bead *bead = start;
    for (int i = 1; i < n; i++)
    {   
        bead->next = new Bead(input[i]);
        bead->next->prev = bead;
        bead = bead->next;
	}
	// complete the circle
    start->prev = bead;
    bead->next = start;

	// break necklace at each bead, counting forwards and backwards
	// each time and storing the max result
	int max = 0;
	for (int i = 0; i < n; i++)
	{
		int forward = 0, backward = 0;
		char c;
		// count forwards
		bead = start;
		while (bead->color == 'w' && forward <= n)
		{
			forward++;
			bead = bead->next;
		}
		c = bead->color;
		while ((bead->color == c || bead->color == 'w') && forward <= n)
		{
			forward++;
			bead = bead->next;
		}
		// count backwards
		bead = start->prev;
		while (bead->color == 'w' && backward <= n)
		{
			backward++;
			bead = bead->prev;
		}
		c = bead->color;
		while ((bead->color == c || bead->color == 'w') && backward <= n)
		{
			backward++;
			bead = bead->prev;
		}
		
		if (max < backward + forward)
			max = backward + forward;

		start = start->next;
	}

	if (max > n)
		max = n;

	fout << max << endl;

	return 0;
}
