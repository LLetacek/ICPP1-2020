#include "CashRegister.h"
#include "Receipt.h"
#include <iostream>
#include <exception>

using namespace std;

void findReceipt(CashRegister* cReg, int id) {
	try {
		Receipt rec = cReg->getReceipt(id);
		cout << "nalezni uctenku s id " << id << ":"
			<< " id:" << rec.getId()
			<< " castka:" << rec.getCost()
			<< " DPH:" << rec.getVat()
			<< endl;
	}
	catch (const char* msg) {
		cout << "!! - " << msg << endl;
	}
}

int main(int argc, char** argv) {
	
	CashRegister cReg(10);

	for (int i = 0; i < 11; i++) {
		try	{
			Receipt receipt = cReg.createReceipt(5 * (i + 1), i * 0.1);
			cout << "uctenka s id: "
				 << receipt.getId()
				 << " - DPH:" 
				 << receipt.getVat()
				 << " - cost:"
				 << receipt.getCost()
				 << endl;
		}
		catch (const char* msg) {
			cout << "!! - " << msg << endl;
		}	
	}

	cout << "SUM: \n" << cReg.getCashVat() << endl << cReg.getCash() << endl;

	findReceipt(&cReg, 1000);
	findReceipt(&cReg, 1009);
	findReceipt(&cReg, 3000);

	system("pause");
	return 0;
}