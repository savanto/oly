/*
ID: washirv1
PROG: zerosum
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
using namespace std;

#define INFILE "zerosum.in"
#define OUTFILE "zerosum.out"

bool zerosum(string s)
{
	int sum = 0, n = 0, m = 1;
	for (int i = s.length() - 1; i >= 0; --i)
	{
		switch (s[i])
		{
			case '+':
				sum += n;
				n = 0;
				m = 1;
				break;
			case '-':
				sum -= n;
				n = 0;
				m = 1;
				break;
			case ' ':
				m *= 10;
				break;
			case '#':
				return false;
			default:
				n += m * (s[i] - 48);
				break;
		}
	}

	sum += n;
	return ! sum;
}

void make(string s, int pos, vector<string> &res)
{
	if (pos < 1)
		return;
	s[pos] = '+';
	if (zerosum(s))
		res.push_back(s);
	make(s, pos - 2, res);
	s[pos] = '-';
	if (zerosum(s))
		res.push_back(s);
	make(s, pos - 2, res);
	s[pos] = ' ';
	if (zerosum(s))
		res.push_back(s);
	make(s, pos - 2, res);
}

int main()
{
	ifstream fin(INFILE);
	int N;
	fin >> N;
	fin.close();

	stringstream ss;
	ss << 1;
	for (int i = 2; i <= N; ++i)
		ss << '#' << i;

	vector<string> res;
	make(ss.str(), N * 2 - 3, res);

	sort(res.begin(), res.end());

	ofstream fout(OUTFILE);
	for (int i = 0; i < res.size(); ++i)
		fout << res[i] << endl;

	fout.close();
	return 0;
}
