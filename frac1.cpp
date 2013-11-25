/*
ID: washirv1
PROG: frac1
LANG: C++
*/

#include <fstream>
using namespace std;

#define INFILE "frac1.in"
#define OUTFILE "frac1.out"


template <class T>
struct Node
{
	T f;
	Node * next, * prev;
	Node(T ff = T(), Node * nxt = NULL, Node * prv = NULL) : f(ff), next(nxt), prev(prv) {}
};

template <class T>
struct List
{
	Node<T> * first;
	Node<T> * last;
	List(T t = T()) : first(new Node<T>(t)), last(first) {}
	void append(T f)
	{ last = last->next = new Node<T>(f, NULL, last); }
	void sort()
	{
		for (Node<T> * i = first->next; i != NULL; i = i->next)
		{
			for (Node<T> * j = i; j != first; j = j->prev)
			{
				if (j->f == j->prev->f)
				{	
					remove(j);
					break;
				}
				else if (j->f < j->prev->f)
					swap(j->f, j->prev->f);
				else
					break;
			}
		}
	}
	void remove(Node<T> * n)
	{
		n->prev->next = n->next;
		n->next->prev = n->prev;
		delete n;
	}
};

template <class T>
ostream & operator<<(ostream & fout, const List<T> & list)
{
	Node<T> * node = list.first;
	while (node != NULL)
	{
		fout << node->f << endl;
		node = node->next;
	}
}

List<int> primes(2);

struct Frac
{
	unsigned int num, den;
	Frac(unsigned int n = 0, unsigned int d = 1) : num(n), den(d)
	{
		// Reduce fraction
		while (num > 1 && den % num == 0)
		{
			den /= num; num /= num;
		}
		if (num > 1)
		{
			Node<int> * n = primes.first;
			while (n != NULL)
			{
				if (num % n->f == 0 && den % n->f == 0)
				{
					num /= n->f; den /= n->f;
				}
				else
					n = n->next;
			}
		}
	}
	friend ostream & operator<<(ostream & fout, const Frac & frac);
	bool operator==(const Frac & rhs) { return num == rhs.num && den == rhs.den; }
	bool operator<(const Frac & rhs) { return num * rhs.den < den * rhs.num; }
};

ostream & operator<<(ostream & fout, const Frac & frac) { fout << frac.num << '/' << frac.den; return fout; }

void swap(Frac & f1, Frac & f2)
{
	unsigned int temp = f1.num;
	f1.num = f2.num;
	f2.num = temp;
	temp = f1.den;
	f1.den = f2.den;
	f2.den = temp;
}

int main()
{
	int N;
	ifstream fin(INFILE);
	fin >> N;
	fin.close();

	List<Frac> fracs;
	primes.append(3);
	for (int i = 5; i < N/2; i+=2)
	{
		Node<int> * n = primes.first;
		bool prime = true;
		while (n != NULL)
		{
			if (i % n->f == 0)
			{
				prime = false;
				break;
			}
			n = n->next;
		}
		if (prime)
			primes.append(i);
	}
	for (unsigned int i = 1; i <= N; ++i)
		for (unsigned int j = N; j > i; --j)
			fracs.append(Frac(i, j));
	fracs.sort();
	fracs.append(Frac(1, 1));

	ofstream fout(OUTFILE);
	fout << fracs;
	fout.close();
	return 0;
}
