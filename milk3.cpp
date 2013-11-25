/*
ID: washirv1
PROG: milk3
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

#define A 0
#define B 1
#define C 2
#define N 3

struct Bucket
{
	int vol, milk;
	Bucket() : vol(0), milk(0) {}
	Bucket(int v) : vol(v), milk(0) {}
	Bucket(int v, int m) : vol(v), milk(m) {}
	int space() { return this->vol - this->milk; }
};

struct State
{
	Bucket b[N];
	State()
	{
		b[A] = Bucket(); b[B] = Bucket(); b[C] = Bucket();
	}
	State(const State &s)
	{
		for (int i = 0; i < N; i++)
			b[i] = s.b[i];
	}
	State(Bucket a_, Bucket b_, Bucket c_)
	{
		b[A] = a_;
		b[B] = b_;
		b[C] = c_;
	}
//	State(Bucket x[N])
//	{
//		for (int i = 0; i < N; i++)
//			b[i] = x[i];
//	}
	State pour(int source, int target)
	{
		State x(*this);//Bucket x[N];
		for (int i = 0; i < N; i++)
			x.b[i] = b[i];
		if (x.b[target].space() >= x.b[source].milk)
		{
			x.b[target].milk += x.b[source].milk;
			x.b[source].milk = 0;
		}
		else
		{
			x.b[source].milk -= x.b[target].space();
			x.b[target].milk = x.b[target].vol;
		}
		return State(x);
	}
	int get(int source) { return b[source].milk; }
};

bool equalBuckets(Bucket a, Bucket b)
{
	return a.milk == b.milk;
}

bool equalStates(State x, State y)
{
	for (int i = 0; i < N; i++)
	{
		if (! equalBuckets(x.b[i], y.b[i]))
			return false;
	}
	return true;
}

int main()
{
	ofstream fout("milk3.out");
	ifstream fin("milk3.in");

	int a, b, c;
	fin >> a >> b >> c;

	State init(Bucket(a), Bucket(b), Bucket(c, c));

	vector<State> v;
	vector<int> sol;
	queue<State> q;
	q.push(init);

	Bucket empty();
	State t, s[6];
	while (q.size() > 0)
	{
		t = State(q.front());
		q.pop();
		v.push_back(t);
		if (t.get(A) == 0)
		{
			bool visited = false;
			for (int i = 0; i < sol.size(); i++)
			{
				if (t.get(C) == sol[i])
					visited = true;
			}
			if (! visited)
				sol.push_back(t.get(C));
		}
		
		s[0] = t.pour(A, B);
		s[1] = t.pour(A, C);
		s[2] = t.pour(B, A);
		s[3] = t.pour(B, C);
		s[4] = t.pour(C, A);
		s[5] = t.pour(C, B);
		for (int i = 0; i < 6; i++)
		{
			bool visited = false;
			for (int j = 0; j < v.size(); j++)
			{
				if (equalStates(s[i], v[j]))
					visited = true;
			}
			if (! visited)
				q.push(s[i]);
		}
	}

	sort(sol.begin(), sol.end());
	for (int i = 0; i < sol.size()-1; i++)
		fout << sol[i] << " ";
	fout << sol[sol.size()-1] << endl;

	return 0;
}
