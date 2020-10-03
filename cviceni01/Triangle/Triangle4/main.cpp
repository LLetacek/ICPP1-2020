#include <iostream> 
using namespace std;

struct Trojuhelnik {
	int a;
	int b;
	int c;

	bool lzeSestrojit()
	{
		return	(this->a + this->b) > (*this).c &&
				(this->a + this->c) > (*this).b &&
				(this->c + this->b) > (*this).a;
	}
};

int main(int argc, char** argv)
{
	Trojuhelnik* t = new Trojuhelnik;
	const char*  outStr = "zadej velikost strany ";

	cout << outStr << "A: ";
	cin >> t->a;
	cout << outStr << "B: ";
	cin >> t->b;
	cout << outStr << "C: ";
	cin >> t->c;

	if (t->lzeSestrojit())
		cout << "obvod vaseho trojuhelnika je: " << (t->a + t->b + t->c) << endl;
	else
		cout << "/!\\ - trojuhelnik nelze sestrojit" << endl;

	delete t;
	
	system("pause");
	return 0;
}