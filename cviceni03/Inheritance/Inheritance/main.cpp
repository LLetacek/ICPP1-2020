#define _USE_MATH_DEFINES

#include <iostream>
#include <cmath>
#include "Game.h"
#include "Monster.h"
#include "StaticObject.h"
#include "TypeOfObstacle.h"

using namespace std;

int main(int argc, char** argv) {

	Game game{20};
	
	try {
		game.insertObject(new StaticObject(0, 0, 0, TypeOfObsticle::rock));
		game.insertObject(new StaticObject(1, 3, 3, TypeOfObsticle::rock));
		game.insertObject(new StaticObject(2, 5, 6, TypeOfObsticle::smallPlant));
		game.insertObject(new StaticObject(3, 6, 6, TypeOfObsticle::bigPlant));

		game.insertObject(new Monster(4, 3, 3, 500));
		game.insertObject(new Monster(5, 4, 3, 666));
		game.insertObject(new Monster(6, 5, 3, 500));

		game.insertObject(new MovingObject(7, 6, 3, 0));
		game.insertObject(new MovingObject(8, 3, 4, M_PI));
		game.insertObject(new MovingObject(9, 4, 4, 2*M_PI));
		game.insertObject(new MovingObject(10, 5, 3, M_PI_2));

		game.insertObject(new Object(-1));
	}
	catch (const char* msg) {
		cout << " ! " << msg << " ! " << endl << endl;
	}

	int iterator = 0;
	cout << "seznam id statickych objektu mezi [0,0] a [4,4]" << endl;
	int* idList = game.findIdStaticObject(0, 0, 4, 4);
	if (idList != nullptr) {
		while (*(idList + iterator) != -1) {
			cout << idList[iterator++] << " ";
		}
		cout << endl;
		delete[] idList;
	}
	
	iterator = 0;
	cout << "seznam id pohyblivych objektu v kruhove oblasti ze stredu [3,3] a polomerem 2" << endl;
	MovingObject** idMovOb = game.findMovingObjectInArea(3,3,2);
	if (idMovOb != nullptr) {
		while (*(idMovOb + iterator) != nullptr) {
			cout << idMovOb[iterator++]->GetId() << " ";
		}
		cout << endl;
		delete[] idMovOb;
	}

	iterator = 0;
	cout << "seznam id pohyblivych objektu v kruhove oblasti ze stredu [4,4] a polomerem 2 natoceny mezi zapadem a jihem" << endl;
	idMovOb = game.findMovingObjectInArea(4, 4, 2, M_PI_2, M_PI);
	if (idMovOb != nullptr) {
		while (*(idMovOb + iterator) != nullptr) {
			cout << idMovOb[iterator++]->GetId() << " ";
		}
		cout << endl;
		delete[] idMovOb;
	}
	
	iterator = 0;
	cout << "seznam id pohyblivych objektu v kruhove oblasti ze stredu [3,3] a polomerem 1 natoceny mezi zapadem a jihem" << endl;
	idMovOb = game.findMovingObjectInArea(3, 3, 1, M_PI_2, M_PI);
	if (idMovOb != nullptr) {
		while (*(idMovOb + iterator) != nullptr) {
			cout << idMovOb[iterator++]->GetId() << " ";
		}
		cout << endl;
		delete[] idMovOb;
	}

	system("pause");
	return 0;
}