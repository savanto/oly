#include <iostream>
using namespace std;

int main()
{
	cout << "bool:      " << sizeof(bool) << endl;
	cout << "char:      " << sizeof(char) << endl;
	cout << "wchar_t:   " << sizeof(wchar_t) << endl;
	cout << "short:     " << sizeof(short) << endl;
	cout << "int:       " << sizeof(int) << endl;
	cout << "size_t:    " << sizeof(size_t) << endl;
	cout << "long:      " << sizeof(long) << endl;
	cout << "long long: " << sizeof(long long) << endl;
	cout << "float:     " << sizeof(float) << endl;
	cout << "double:    " << sizeof(double) << endl;

	cout << "short *:   " << sizeof(short*) << endl;
	cout << "int *:     " << sizeof(int*) << endl;
	cout << "long *:    " << sizeof(long*) << endl;
	return 0;
}
