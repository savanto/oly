#include <iostream>
#include <vector>
using namespace std;

bool find(const vector<int> &set, int x)
{
	for (int i = 0; i < set.size(); i++)
	{
		if (set[i] == x)
			return true;
	}
	return false;
}

void print(const vector<int> &set, int x)
{
	for (int i = 0; i < set.size(); i++)
		cout << set[i];
	cout << x << endl;
}

void choose(vector<int> &set, vector<int> &subset, int k)
{
	if (k == 1)
	{
		for (int i = 0; i < set.size(); i++)
		{
			if (! find(subset, set[i]))
				print(subset, set[i]);
		}
		return;
	}
	vector<int> sub;
	bool used;
	for (int i = 0; i < set.size(); i++)
	{
		sub = subset;
		used = false;
		for (int j = 0; j < subset.size(); j++)
		{
			if (set[i] == subset[j])
				used = true;
		}
		if (! used)
		{
			sub.push_back(set[i]);
			choose(set, sub, k-1);
		}
	}
}
	

int main()
{
	int n = 8, k = 4, i;
	vector<int> set(n, 0), subset;
	for (i = 0; i < n; i++)
		set[i] = i+1;

	choose(set, subset, k);

	return 0;
}
