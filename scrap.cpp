#include <iostream>
using namespace std;

int main()
{
	int bits[64] = { 0 };
	for (int i = 0; i < 64; i += 3)
		bits[i] = 1;
	for (int i = 63; i >= 0; --i)
		cout << bits[i];
	cout << endl;
	return 0;
}
