#include "Person.h"
#include <fstream>
using namespace std;

void save(int count, Person* arrP) {
	if (count <= 0)
		return;

	ofstream out{};
	out.open("save.txt");
	if (out.is_open()) {
		out << count << endl;
		for (int i = 0; i < count; ++i) {
			out << arrP[i] << endl;
		}
		out.close();
	}
	else {
		cerr << "Soubor se nepodarilo otevrit";
	}
}

void load() {
	Person p{};
	int count;

	ifstream in{};
	in.open("save.txt");
	if (in.is_open()) {
		in >> count;
		for (int i = 0; i < count; i++) {
			in >> p;
			cout << p << endl;
		}
		in.close();
	}
	else {
		cerr << "Soubor se nepodarilo otevrit";
	}
}

void saveBin(int count, Person* arrP) {
	if (count <= 0)
		return;

	ofstream out("save.dat", ios_base::binary);
	if (out.is_open()) {
		out.write((const char*)&count, sizeof(count));
		for (int i = 0; i < count; ++i) {
			Person tmp = arrP[i];
			out.write((const char*)&tmp, sizeof tmp);
		}
		out.close();
	}
	else {
		cerr << "Soubor se nepodarilo otevrit";
	}
}

void loadBin() {
	Person* people = nullptr;
	int count = 0;
	ifstream in{};
	in.open("save.dat", std::ios_base::binary);
	if (in.is_open())
	{
		in.read((char*)&count, sizeof count);
		people = new Person[count];
		for (int i = 0; i < count; i++)
		{
			in.read((char*)&people[i], sizeof(Person));
			cout << people[i] << endl;
		}
		in.close();
	}
	else {
		cerr << "Soubor se nepodarilo otevrit";
	}

	if(people!= nullptr)
		delete[] people;
}

int main(int argc, char** argv) {

	Person p1{ "Bjarne", "Stroustrup", Address{"Vestergade","Aarhus",8000}, Date{30, 12, 1950} };
	Person p2{ "Scott", "Meyers", Address{"Riverside Drive","New York",10023}, Date{9, 4, 1959} };
	Person p3{ "Dennis", "Ritchie", Address{"Berkeley","New Jersey",7069}, Date{9, 9, 1941} };

	cout << p1 << endl << p2 << endl << p3 << endl;

	Person* arrP = new Person[3];

	arrP[0] = p1;
	arrP[1] = p2;
	arrP[2] = p3;

	cout << "= ulozeno =" << endl;
	save(3, arrP);

	cout << "= nacteno =" << endl;
	load();

	cout << "= ulozen bin =" << endl;
	saveBin(3, arrP);

	cout << "= nacten bin =" << endl;
	loadBin();

	delete[] arrP;

	return 0;
}