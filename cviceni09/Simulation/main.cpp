#include <iostream>
#include <fstream>
#include <sstream>
#include "PipeElement.h"
using namespace std;

void nacti(string file) {
	IPipe* pipe = nullptr;
	string skip;
	int size;
	char character;
	ifstream in{};
	in.open(file);

	if (in.is_open()) {
		while (true) {
			in >> size;
			std::getline(in, skip, '\n');
			pipe = new Pipe(size);

			if (pipe == nullptr)
				continue;

			for (int y = 0; y <= pipe->GetSize(); ++y) {
				for (int x = 0; x <= pipe->GetSize(); ++x) {
					character = in.get();

					if (character == '-') {
						new PipeElementMinus(x, y, pipe);
					}
					else if (character == '+') {
						new PipeElementPlus(x, y, pipe);
					}
					else if (character == 'I') {
						new PipeElementI(x, y, pipe);
					}
					else if (character == 'T') {
						new PipeElementT(x, y, pipe);
					}
					else if (character == 'O') {
						new PipeElementO(x, y, pipe);
					}
					else if (character == ' ') {
						continue;
					}
					else {
						if (character != '\n')
							std::getline(in, skip, '\n');
						break;
					}
				}
			}

			skip = (pipe->IsPipeOk()) ? "OK" : "NOT OK";
			cout << skip << endl;

			if (pipe != nullptr)
				delete pipe;

			if (in.eof()) 
				break;

			in >> skip;
			std::getline(in,skip,'\n');
		}
		in.close();
	}
	else {
		cerr << "Soubor se nepodarilo otevrit";
	}

}

int main(int argc, char** argv) {

	nacti("pipe.txt");

	return 0;
}