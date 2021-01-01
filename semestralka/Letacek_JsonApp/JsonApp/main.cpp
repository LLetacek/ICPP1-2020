#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include <sstream>
#include <fstream>
#include "Airplane.h"

// - kontrola, ze za poslednim parametrem, resp. jednim prikazem neni dalsi parametr, resp. parametr nebo dalsi prikaz.
bool endOfCommand(const std::string expectedEnd, const std::string line) {
	std::stringstream stream;
	std::size_t pos = line.find(expectedEnd);
	std::string cmdline;
	try {
		cmdline = line.substr(pos);
	}
	catch (...) {
		return false;
	}

	stream << cmdline.substr(expectedEnd.size());
	cmdline.clear();
	stream >> cmdline;
	return (cmdline.empty());
}

bool isUnsignedNumber(std::string str) {
	for (unsigned int i = 0; i < str.size(); ++i) {
		if (!(48 <= str[i] && str[i] <= 57))
			return false;
	}
	return true;
}

std::string askYesOrNo(std::string question) {
	std::string input, command;
	std::stringstream stream;
	do {
		std::cout << question;
		std::getline(std::cin, input);
		stream.clear();
		stream.str(input);
		stream >> command;
	} while (!endOfCommand(command, input) || (command.compare("ano") != 0 && command.compare("ne") != 0));
	return command;
}

std::string ask(std::string question) {
	std::cout << question;
	std::string ans;
	std::getline(std::cin, ans);
	return ans;
}

Airport* createAirport() {
	Airport* airport = new Airport{};
	std::string input;
	std::cout << "\ticao (muzete nechat prazdne): ";
	std::getline(std::cin, input);
	airport->setIcao(input);
	std::cout << "\tpoloha (muzete nechat prazdne): ";
	std::getline(std::cin, input);
	airport->setPlace(input);
	return airport;
}

void editPlane(Airplane* plane) {
	std::string input;
	std::stringstream stream;

	while (true) {
		stream.clear();
		std::cout << "editace(" << plane->getKey() << ")# ";
		std::getline(std::cin, input);

		std::string command;
		stream.str(input);
		stream >> command;

		if (!endOfCommand(command, input)) {
			std::cout << " ZADEJTE POUZE JEDEN PRIKAZ!" << std::endl;
			continue;
		}

		if (command.compare("exit") == 0) {
			break;
		}
		else if (command.compare("detail") == 0) {
			std::cout << plane->toString() << std::endl;
		}
		else if (command.compare("letiste") == 0) {
			Airport* airport = createAirport();
			plane->setAirport(airport);
		}
		else if (command.compare("rychlost") == 0) {
			std::string speed;
			std::cout << "\tmax rychlost (muzete nechat prazdne): ";
			std::getline(std::cin, speed);
			if (speed.empty())
				speed = "0";

			if (!isUnsignedNumber(speed)) {
				std::cout 
					<< "Musite zadat kladne cislo\n(enter nebo nulu, pokud nechcete tuto informaci poskytnout)" 
					<< std::endl;
				continue;
			}
			
			plane->setMaxSpeed(std::stoi(speed));
		}
		else if (command.compare("kontrola") == 0) {
			std::string inspec;
			std::cout << "\tpridat kontrolu: ";
			std::getline(std::cin, inspec);
			plane->appendInspection(inspec);
		}
		else if (command.compare("letuschopnost") == 0) {
			std::string letuschopnost = askYesOrNo("\tletuschopne (ano/ne): ");
			plane->setAirworthy(letuschopnost.compare("ano") == 0);
		}
		else if (command.compare("?") == 0) {
			std::cout
				<< " detail\t\t-> zobrazi detail letadla" << std::endl
				<< " letiste\t-> opravi domovske letiste" << std::endl
				<< " rychlost\t-> opravi maximalni rychlost" << std::endl
				<< " kontrola\t-> prida na konec seznamu kontrolu" << std::endl
				<< " letuschopnost\t-> upravi letuschopnost letadla" << std::endl
				<< " exit\t\t-> ukonci editaci" << std::endl
				<< " ?\t\t-> zobrazi napovedu" << std::endl << std::endl;
		}
		else if (!command.empty()) {
			std::cout << " NEPLATNY PRIKAZ!" << std::endl;
		}
	}
}

bool editation(DynamicArray<Airplane*>* queue) {
	std::cout << std::endl << std::endl << "---------------------" << std::endl
		<< queue->serializeAll(&Airplane::getKey) << std::endl << std::endl;

	std::string input;
	std::stringstream stream;

	while (true) {
		stream.clear();
		std::cout << "editace# ";
		std::getline(std::cin, input);

		std::string command;
		stream.str(input);
		stream >> command;

		if (!endOfCommand(command, input)) {
			std::cout << " ZADEJTE POUZE JEDEN PRIKAZ!" << std::endl;
			continue;
		}

		if (command.compare("exit") == 0) {
			break;
		}
		else if (command.compare("uprav") == 0) {
			try {
				Airplane* plane = queue->findByKey(&Airplane::equalityOfKeys, ask("Zadejte imatrikulaci: "));
				editPlane(plane);
			}
			catch (...) {
				std::cout << "Letadlo s touto imatrikulaci neni ve fronte!" << std::endl;
			}
		}
		else if (command.compare("vloz") == 0) {
			Airport* airport = nullptr;
			std::string* arr = new std::string[4];
			std::cout << "NOVE LETADLO: " << std::endl
					<< "\timatrikulace: ";
			std::getline(std::cin, arr[0]);
			std::cout << "\tnazev: ";
			std::getline(std::cin, arr[1]);
			std::string create = askYesOrNo("\tzadat domovske letiste (ano/ne): ");
			if (create.compare("ano")==0) {
				airport = createAirport();
			}
			std::cout << "\tmax rychlost (muzete nechat prazdne): ";
			std::getline(std::cin, arr[2]);
			if (arr[2].empty())
				arr[2] = "0";

			arr[3] = askYesOrNo("\tletuschopne (ano/ne): ");

			if (arr[0].empty() || arr[1].empty() || !isUnsignedNumber(arr[2])) {
				delete[] arr;
				std::cout << "Na zaklade vasich vstupu nelze letadlo vytvorit" << std::endl;
				continue;
			}

			queue->append(new Airplane(arr[0], arr[1], airport, std::stoi(arr[2]),arr[3].compare("ano")==0));

			delete[] arr;
			std::cout << "HOTOVO!\n(Chcete-li pridat datumy kontrol k tomuto letadlu -> zadejte prikaz \"uprav\")" << std::endl;
		}
		else if (command.compare("detail") == 0) {
			try {
				std::cout 
					<< (queue->findByKey(&Airplane::equalityOfKeys, ask("Zadejte imatrikulaci: ")))->toString()
					<< std::endl;
			}
			catch (...) {
				std::cout << "Letadlo s touto imatrikulaci neni ve fronte!" << std::endl;
			}
		}
		else if (command.compare("odeber") == 0) {
			try {
				Airplane* tmp = queue->remove();
				std::cout << "NA RADE K OPRAVE/KONTROLE JE:\n" << tmp->toString() << std::endl;
				delete tmp;
			}
			catch (...) {
				std::cout << "fronta je jiz prazdna!" << std::endl;
			}
		}
		else if (command.compare("zobraz") == 0) {
			std::cout << queue->serializeAll(&Airplane::getKey) << std::endl;
		}
		else if (command.compare("uloz") == 0) {
			std::string cesta = "../FrontaOpravSave.json";
			command = askYesOrNo("Chcete pouzit vychozi cestu k souboru JSON pro ulozeni (ano/ne): ");

			if (command.compare("ne") == 0) {
				std::cout << "Zadejte cestu k souboru: ";
				std::getline(std::cin, cesta);
			}

			std::ofstream myfile(cesta);
			if (myfile.is_open())
			{
				ArrayValue* arr = new ArrayValue{};
				for (int i = 0; i < queue->getSize(); ++i) {
					arr->append(queue->getElementAt(i)->getJSON());
				}
				myfile << JSON::serialize(arr);
				myfile.close();
				delete arr;
				continue;
			}
			std::cout << "Chyba u ukladani do souboru! - zkontrolujte cestu" << std::endl;
		}
		else if (command.compare("?") == 0) {
			std::cout 
				<< " uprav\t-> upravi letadlo" << std::endl
				<< " detail\t-> zobrazi detail letadla" << std::endl
				<< " odeber\t-> odebere prvniho z fronty" << std::endl
				<< " vloz\t-> vloz dalsi letadlo k oprave" << std::endl
				<< " zobraz\t-> zobrazi frontu" << std::endl
				<< " uloz\t-> ulozi frontu do souboru JSON" << std::endl
				<< " exit\t-> ukonci editaci" << std::endl
				<< " ?\t-> zobrazi napovedu" << std::endl << std::endl;
		}
		else if (!command.empty()) {
			std::cout << " NEPLATNY PRIKAZ!" << std::endl;
		}
	}

	return false;
}

bool load(std::string filePath) {
	std::ifstream file;
	file.open(filePath);

	if (file.is_open()) {
		std::stringstream stream;
		stream << file.rdbuf();
		std::string str = stream.str();
		file.close();

		DynamicArray<Airplane*> queue{};
		Value* test = nullptr;
		try {
			test = JSON::deserialize(str);
			ArrayValue* arr = dynamic_cast<ArrayValue*>(test);
			
			if (arr) {
				for (int i = 0; i < arr->getSize(); ++i) {
					queue.append(new Airplane{ arr->getElementAt(i) });
				}
			}
			
			bool exit = editation(&queue);

			for (int i = 0; i < queue.getSize(); ++i) {
				delete queue.getElementAt(i);
			}
			
			delete test;
			return exit;
		}
		catch (const std::invalid_argument& content) {
			for (int i = 0; i < queue.getSize(); ++i) {
				delete queue.getElementAt(i);
			}

			if (test)
				delete test;
			std::cout << content.what() << std::endl;
			return false;
		}
	}

	std::cout << "Nepodarilo se soubor otevrit!" << std::endl;
	return false;
}

void start() {
	std::string input;

	std::stringstream stream;
	std::cout << "\tUPRAVA FRONTY LETADEL PRO OPRAVU/KONTROLU" << std::endl
		<< "-------------------------------------------------------------" << std::endl;
	std::cout << "pro napovedu napiste \"?\"" << std::endl << std::endl;

	while (true) {
		stream.clear();
		std::cout << "uvod> ";
		std::getline(std::cin, input);

		std::string command;
		stream.str(input);
		stream >> command;

		if (!endOfCommand(command, input)) {
			std::cout << " ZADEJTE POUZE JEDEN PRIKAZ!" << std::endl;
			continue;
		}
		
		if (command.compare("exit") == 0) {
			break;
		}
		else if (command.compare("nacti") == 0) {
			std::string cesta = "../FrontaOprav.json";
			command = askYesOrNo("Chcete pouzit vychozi cestu k souboru JSON (ano/ne): ");

			if (command.compare("ne") == 0) {
				std::cout << "Zadejte cestu k souboru: ";
				std::getline(std::cin, cesta);
			}

			if (load(cesta))
				break;
		}
		else if (command.compare("?") == 0) {
			std::cout 
				<< " nacti\t-> natcte JSON soubor fronty a spusti se editovaci mode" << std::endl
				<< " exit\t-> ukonci aplikaci" << std::endl
				<< " ?\t-> zobrazi napovedu" << std::endl << std::endl;
		}
		else if (!command.empty()) {
			std::cout << " NEPLATNY PRIKAZ!" << std::endl;
		}
	}
}

//------------------

int main() {
	
	start();

	_CrtDumpMemoryLeaks();
	return 0;
}