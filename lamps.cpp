/*
ID: washirv1
PROG: lamps
LANG: C++
*/

#include <iostream>
#include <fstream>
using namespace std;

#define INFILE "lamps.in"
#define OUTFILE "lamps.out"

#define ODD		0x5555555555555555
#define EVEN	0xAAAAAAAAAAAAAAAA
#define THREES	0x9249249249249249
#define ON		0xFFFFFFFFFFFFFFFF
#define OFF		0x0000000000000000
typedef unsigned long long int Lamps;
int N, C;

struct Config
{
	Lamps a, b;
	Config(Lamps aa = 0, Lamps bb = 0) : a(aa), b(bb) {}
	Config(const Config & copy) : a(copy.a), b(copy.b) {}
	Config & operator=(const Config & rhs) { a = rhs.a; b = rhs.b; return *this; }
	Config & operator+=(const int lamp)
	{
		if (lamp >= 64)
			b |= 1 << lamp-1;
		else
			a |= 1 << lamp-1;
		return *this;
	}
	Config & operator-=(const int lamp)
	{
		if (lamp >= 64)
			b &= ~(1 << lamp-1);
		else
			a &= ~(1 << lamp-1);
		return *this;
	}
	Config & operator&=(const Config & rhs)
	{ a &= rhs.a; b &= rhs.b; return *this; }
	Config & operator|=(const Config & rhs)
	{ a |= rhs.a; b |= rhs.b; return *this; }
	Config button1() { return Config(~a, ~b); }
	Config button2() { return Config(a ^ ODD, b ^ ODD); }
	Config button3() { return Config(a ^ EVEN, b ^ EVEN); }
	Config button4() { return Config(a ^ THREES, b ^ THREES); }
	Config button(int b)
	{
		switch (b)
		{
			case 1: return button1();
			case 2: return button2();
			case 3: return button3();
			case 4: return button4();
			default: return Config(*this);
		}
	}
};
ostream & operator<<(ostream & os, const Config & lamps)
{
	int n = N, i;
	Lamps bit;
	for (i = 0, bit = 1; i < 64 && n > 0; ++i, --n, bit <<= 1)
		os << (lamps.a & bit ? 1 : 0);
	for (bit = 1; n > 0; --n, bit <<= 1)
		os << (lamps.b & bit ? 1 : 0);
	return os;
}
inline Config operator&(Config lhs, const Config & rhs)
{ lhs &= rhs; return lhs; }
inline Config operator|(Config lhs, const Config & rhs)
{ lhs |= rhs; return lhs; }

int main()
{
	ifstream fin(INFILE);
	fin >> N >> C;
	int lamp;
	fin >> lamp;
	Config CHECK_ON(OFF, OFF), CHECK_OFF(ON, ON);
	while (lamp != -1)
	{
		CHECK_ON += lamp;
		fin >> lamp;
	}
	fin >> lamp;
	while (lamp != -1)
	{
		CHECK_OFF -= lamp;
		fin >> lamp;
	}
	fin.close();

	Config lamps(ON, ON);
	C %= 4;
	int L = C;//1;
//	for (; C > 0; --C)
//		L *= 2;

	for (int b1 = 0; b1 < L; ++b1)
	{
		for (int b2 = 0; b2 < L; ++b2)
		{
			for (int b3 = 0; b3 < L; ++b3)
			{
				for (int b4 = 0; b4 < L; ++b4)
				{
		Config test = lamps.button(1);
		cout << test << endl;
			test = test.button(2);
			cout << test << endl;
				test = test.button(3);
				cout << test << endl;
					test = test.button(4);
					cout << test << endl;
				}
			}
		}
	}



	ofstream fout(OUTFILE);

	fout.close();
	return 0;
}
