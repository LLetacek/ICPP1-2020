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
	
	Object* obj01 = nullptr;
	Object* obj02 = nullptr;
	Object* obj03 = nullptr;
	Object* obj04 = nullptr;
	Object* obj05 = nullptr;
	Object* obj06 = nullptr;
	Object* obj07 = nullptr;
	Object* obj08 = nullptr;
	Object* obj09 = nullptr;
	Object* obj10 = nullptr;
	Object* obj11 = nullptr;
	Object* obj12 = nullptr;

	try {
		obj01 = new StaticObject(0, 0, 0, TypeOfObsticle::rock);
		obj02 = new StaticObject(1, 3, 3, TypeOfObsticle::rock);
		obj03 = new StaticObject(2, 5, 6, TypeOfObsticle::smallPlant);
		obj04 = new StaticObject(3, 6, 6, TypeOfObsticle::bigPlant);
		obj05 = new Monster(4, 3, 3, 500);
		obj06 = new Monster(5, 4, 3, 666);
		obj07 = new Monster(6, 5, 3, 500);
		obj08 = new MovingObject(7, 6, 3, 0);
		obj09 = new MovingObject(8, 3, 4, M_PI);
		obj10 = new MovingObject(9, 4, 4, 2 * M_PI);
		obj11 = new MovingObject(10, 5, 3, M_PI_2);

		obj12 = new Object(-1); // throws exception - nullptr
	}
	catch (const char* msg) {
		cout << " ! " << msg << " ! " << endl << endl;
	}

	game.insertObject(obj01);
	game.insertObject(obj02);
	game.insertObject(obj03);
	game.insertObject(obj04);
	game.insertObject(obj05);
	game.insertObject(obj06);
	game.insertObject(obj07);
	game.insertObject(obj08);
	game.insertObject(obj09);
	game.insertObject(obj10);
	game.insertObject(obj11);

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

	delete obj01;
	delete obj02;
	delete obj03;
	delete obj04;
	delete obj05;
	delete obj06;
	delete obj07;
	delete obj08;
	delete obj09;
	delete obj10;
	delete obj11;

	system("pause");
	return 0;
}