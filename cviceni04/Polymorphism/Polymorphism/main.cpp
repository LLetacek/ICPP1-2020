#include <iostream>
#include <ctime>
#include "Time.h"

#define ARRAY_SIZE 10

void SortArray(IComparable** array, int size) {
	try {
		for (int i = 0; i < size - 1; i++) {
			for (int j = 0; j < size - i - 1; j++) {
				if (array[j + 1]->CompareTo(array[j]) == 1) {
					IComparable* tmp = array[j + 1];
					array[j + 1] = array[j];
					array[j] = tmp;
				}
			}
		}
	}
	catch (const char*) {
		std::cout << "chyba u CompareTo" << std::endl;
	}
}

int random (int min, int max) {
	return rand() % (max - min) + min;
}

void printOut(Time** time, int size) {
	for (int i = 0; i < ARRAY_SIZE; i++) {
		std::cout << time[i]->ToString() << std::endl;
	}
	std::cout << "--------" << std::endl;
}

int main(int argc, char** argv) {

	Time** time = new Time*[ARRAY_SIZE];

	std::srand(std::time(0));
	for (int i = 0; i < ARRAY_SIZE; i++) {
		time[i] = new Time(random(0,23), random(0,59), random(0,59));
	}

	printOut(time, ARRAY_SIZE);
	SortArray((IComparable**)time, ARRAY_SIZE);
	printOut(time, ARRAY_SIZE);

	for (int i = 0; i < ARRAY_SIZE; i++) {
		delete time[i];
	}
	delete[] time;

	system("pause");
	return 0;
}
