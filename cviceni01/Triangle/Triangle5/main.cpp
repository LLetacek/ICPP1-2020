#include <iostream> 
using namespace std;

struct Trojuhelnik {
	int a;
	int b;
	int c;

	bool lzeSestrojit()
	{
		return	(a + b) > c &&
				(a + c) > b &&
				(c + b) > a;
	}
};

int main(int argc, char** argv)
{
	Trojuhelnik* pole;
	const char*  outStr = "zadej velikost strany ";
	int pocet;

	cout << "kolik chcete nacist trojuhelniku: ";
	cin >> pocet;

	if (pocet <= 0)
	{
		system("pause");
		return 0;
	}

	pole = new Trojuhelnik[pocet];

	for (int i = 0; i < pocet; i++)
	{
		cout << endl << "TROJUHELNIK " << (i + 1) << endl;

		cout << outStr << "A: ";
		cin >> (pole+i)->a;
		cout << outStr << "B: ";
		cin >> i[pole].b;
		cout << outStr << "C: ";
		cin >> (*(pole + i)).c;

		if (pole[i].lzeSestrojit())
			cout << "obvod vaseho trojuhelnika je: " << (pole[i].a + pole[i].b + pole[i].c) << endl;
		else
			cout << "/!\\ - trojuhelnik nelze sestrojit" << endl;
	}

	delete[] pole;

	system("pause");
	return 0;
}