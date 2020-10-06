#include <iostream> 
using namespace std;

struct Trojuhelnik {
	int a;
	int b;
	int c;
};

bool lzeSestrojit(Trojuhelnik* t)
{
	return	(t->a + t->b) > t->c &&
			(t->a + t->c) > t->b &&
			(t->c + t->b) > t->a;
}

int main(int argc, char** argv)
{
	Trojuhelnik  t;
	Trojuhelnik* ukazatel = &t;
	const char*  outStr   = "zadej velikost strany ";

	cout << outStr << "A: ";
	cin >> ukazatel->a;
	cout << outStr << "B: ";
	cin >> ukazatel->b;
	cout << outStr << "C: ";
	cin >> ukazatel->c;

	if (lzeSestrojit(ukazatel))
	{
		cout << "obvod vaseho trojuhelnika je: " << (ukazatel->a + ukazatel->b + ukazatel->c) << endl;
	}
	else
	{
		cout << "/!\\ - trojuhelnik nelze sestrojit" << endl;
	}

	system("pause");
	return 0;
}