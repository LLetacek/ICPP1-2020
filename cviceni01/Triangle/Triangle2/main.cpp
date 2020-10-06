#include <iostream> 
using namespace std;

struct Trojuhelnik {
	int a;
	int b;
	int c;
};

bool lzeSestrojit (Trojuhelnik t)
{
	return	(t.a + t.b) > t.c &&
			(t.a + t.c) > t.b &&
			(t.c + t.b) > t.a;
}

int main(int argc, char** argv)
{
	Trojuhelnik t;
	const char* outStr = "zadej velikost strany ";

	cout << outStr << "A: ";
	cin >> t.a;
	cout << outStr << "B: ";
	cin >> t.b;
	cout << outStr << "C: ";
	cin >> t.c;

	if (lzeSestrojit(t))
	{
		cout << "obvod vaseho trojuhelnika je: " << (t.a + t.b + t.c) << endl;
	}
	else
	{
		cout << "/!\\ - trojuhelnik nelze sestrojit" << endl;
	}

	system("pause");
	return 0;
}