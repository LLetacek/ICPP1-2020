#include "CashRegister.h"
#include <exception>

#define INIT_ID 1000

int CashRegister::m_idCounter;

CashRegister::CashRegister(int receipts) :  m_receipts(new Receipt[receipts]),
											m_maxId(receipts) {
}

CashRegister::~CashRegister() {
	delete[] m_receipts;
}

Receipt& CashRegister::createReceipt(double cost, double vat) {
	if (m_idCounter < m_maxId) {
		m_receipts[m_idCounter].setCost(cost);
		m_receipts[m_idCounter].setId(INIT_ID + m_idCounter);
		m_receipts[m_idCounter].setVat(vat);
		return m_receipts[m_idCounter++];
	}
	throw "too many receipts";
}

Receipt& CashRegister::getReceipt(int id) {
	for (int i = 0; i < m_idCounter; i++) {
		if (m_receipts[i].getId() == id)
			return m_receipts[i];
	}

	if (m_idCounter == 0) {
		throw "no receipt to return";
	}

	return m_receipts[0];
}

double CashRegister::getCash() const {
	double sum = 0;
	for (int i = 0; i < m_idCounter; i++) {
		sum += m_receipts[i].getCost();
	}
	return sum;
}

double CashRegister::getCashVatBasis() {
	double sum = 0;
	for (int i = 0; i < m_idCounter; i++) {
		sum += m_receipts[i].getCost() * (1 + m_receipts[i].getVat());
	}
	return sum;
}