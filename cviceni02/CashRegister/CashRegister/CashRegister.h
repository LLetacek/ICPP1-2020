#pragma once
#ifndef CASH_REGISTER_H
#define CASH_REGISTER_H

#include "Receipt.h"

class CashRegister {
 public:
	 CashRegister(int maxReceipts);
	 ~CashRegister();

	 Receipt& createReceipt(double cost, double vat);
	 Receipt& getReceipt(int id);
	 double getCash() const;
	 double getCashVatBasis();

 private:
	Receipt *	m_receipts;
	int			m_maxId;
	static int	m_idCounter;
};

#endif // !CASH_REGISTER_H
