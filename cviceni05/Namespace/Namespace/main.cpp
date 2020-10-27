#include <iostream>

#include "Model.h"

using namespace Model;
using namespace Entities;
using namespace std;

int main(int argc, char** argv) {
	
	Phonebook book{};

	try {
		book.AddPerson(Person(0, "Bjarne Stroustrup", "111 111 111"));
		book.AddPerson(Person(1, "Scott Meyers"     , "123 123 123"));
		book.AddPerson(Person(2, "Andrew Koenig"    , "321 321 321"));
		book.AddPerson(Person(3, "Brian Kernighan"  , "333 444 555"));
		book.AddPerson(Person(4, "Dennis Ritchie"   , "194 102 011"));
	} catch (const char* e) {
		cout << e << endl << endl;
	}

	try {
		cout << "expected: \"111 111 111\" - get: \"";
		cout << book.FindPhone(0);
		cout << "\"" << endl << "expected: \"111 111 111\" - get: \"";
		cout << book.FindPhone("Bjarne Stroustrup");

		cout << "\"" << endl << "expected: \"194 102 011\" - get: \"";
		cout << book.FindPhone(4);
		cout << "\"" << endl << "expected: \"194 102 011\" - get: \"";
		cout << book.FindPhone("Dennis Ritchie");

		cout << "\"" << endl << "expected: \"321 321 321\" - get: \"";
		cout << book.FindPhone(2);
		cout << "\"" << endl << "expected: \"321 321 321\" - get: \"";
		cout << book.FindPhone("Andrew Koenig");

		cout << "\"" << endl << endl;
	} catch (const char* e) {
		cout << e << endl;
	}

	cout << "| KONTROLA VYJIMEK |" << endl;

	try {
		book.AddPerson(Person(-1, "James Gosling", "666 666 666"));
	}
	catch (const char* e) {
		cout << "pridani osoby s id[-1]: " 
			 << endl << e << endl << endl;
	}

	try {
		book.FindPhone("James Gosling");
	}
	catch (const char* e) {
		cout << "hledani osoby s neexistujicim jmenem v seznamu: " 
			 << endl << e << endl << endl;
	}

	try {
		book.FindPhone(-1);
	} catch (const char* e) {
		cout << "hledani osoby s id[-1]: " 
			 << endl << e << endl << endl;
	}

	try {
		book.FindPhone("");
	} catch (const char* e) {
		cout << "hledani osoby se jmenem prazdneho retezce: " 
			 << endl << e << endl << endl;
	}

	system("pause");
	return 0;
}