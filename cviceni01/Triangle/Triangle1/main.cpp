#include <iostream> 
using namespace std;

int main(int argc, char** argv)
{
	int   a;
	int   b;
	int   c;
	const char* outStr = "zadej velikost strany ";

	cout << outStr << "A: ";
	cin >> a;
	cout << outStr << "B: ";
	cin >> b;
	cout << outStr << "C: ";
	cin >> c;

	if ((a + b) > c && (a + c) > b &&  (c + b) > a)
	{
		cout << "obvod vaseho trojuhelnika je: " << (a + b + c) << endl;
	}
	else
	{
		cout << "/!\\ - trojuhelnik nelze sestrojit" << endl;
	}

	system("pause");
	return 0;
}