/*
ID: washirv1
PROG: milk
LANG: C++
*/
#include <iostream>
#include <fstream>
using namespace std;

void swap(int array[], int a, int b)
{
	int temp = array[a];
	array[a] = array[b];
	array[b] = temp;
}

int partition(int array[], int slave[], int left, int right, int pivot)
{
	int value = array[pivot];
	swap(array, pivot, right);
	swap(slave, pivot, right);
	int store = left;
	for (int i = left; i < right; i++)
	{
		if (array[i] < value)
		{
			swap(array, i, store);
			swap(slave, i, store);
			store++;
		}
	}
	swap(array, store, right);
	swap(slave, store, right);
	return store;
}

void quicksort(int array[], int slave[], int left, int right)
{
	if (left < right)
	{
		int pivot = (left + right) / 2;
		pivot = partition(array, slave, left, right, pivot);
		quicksort(array, slave, left, pivot - 1);
		quicksort(array, slave, pivot + 1, right);
	}
}

int main()
{
	ofstream fout("milk.out");
	ifstream fin("milk.in");

	int n, m;
	fin >> n >> m;

	int p[m];
	int q[m];
	for (int i = 0; i < m; i++)
		fin >> p[i] >> q[i];

	quicksort(p, q, 0, m - 1);

	int cost, i;
	for (cost = 0; n > 0 && i < m; i++)
	{
		n -= q[i];
		if (n >= 0)
			cost += q[i] * p[i];
		else
			cost += (q[i] + n) * p[i];
	}

	fout << cost << endl;

	return 0;
}
