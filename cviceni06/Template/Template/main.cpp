#include <iostream>
#include "ExpandingContainer.h"

using namespace std;

void test() {
	for (int i = 0; i <= 10; i++) {
		try {
			switch (i) {
			case 0: {
				// err
				ExpandingContainer<string, 0> err;
				break;
				}
			case 1: {
				// err
				ExpandingContainer<string, 5, 0> err;
				break;
				}
			case 2: {
				// err
				ExpandingContainer<string, 0, 0> err;
				break;
				}
			case 3: {
				// err
				ExpandingContainer<string, 5, 1> err;
				break;
				}
			default:
				break;
			}

			ExpandingContainer<string> test;
			test.Add(":)");
			test.Add(":(");
			test.Add(":/");

			switch (i) {
			case 4: {
				// err
				string tmp = test[-1];
				break;
				}
			case 5:
				// err
				test[3] = ":D";
				break;
			case 6:
				// err
				test.AddTo(4, ":*");
				break;
			case 7:
				// err
				test.Remove(4);
				break;
			case 8:
				// err
				test.AddTo(-1, ":*");
				break;
			case 9:
				// err
				test.Remove(-1);
				break;
			default:
				cout << "-------" << endl;
				break;
			}

			test.AddTo(3, ":))");
			test.AddTo(0, ":|");
			test.Add(":'(");
			test[4] = ":)))";
			test[5] = "-_-";
			test[4] = test[5];

			cout << "pocet vlozenych prvku: " << test.Size() << endl;
			cout << "prvky: ";
			for (unsigned int j = 0; j < test.Size(); j++) {
				cout << "- \"" << test[j] << "\" ";
			}
			cout << endl;

			test.Remove(0);
			test.Remove(4);

			cout << "pocet vlozenych prvku: " << test.Size() << endl;
			cout << "prvky: ";
			for (unsigned int j = 0; j < test.Size(); j++) {
				cout << "- \"" << test[j] << "\" ";
			}
			cout << endl;
		}
		catch (exception& e) {
			cout << "ERR: " << e.what() << endl;
		}
	}
}

int main(int agrc, char** argv) {

	test();

	return 0;
}
