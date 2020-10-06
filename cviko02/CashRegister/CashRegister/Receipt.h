#pragma once
#ifndef RECEIPT_H
#define RECEIPT_H

class Receipt {
 public:
	 Receipt(int id, double cost, double vat);
	 Receipt();
	 ~Receipt();

	 void	setId(int id);
	 void	setCost(double cost);
	 void	setVat(double vat);
	 int	getId() const;
	 double	getCost() const;
	 double	getVat() const;

private:
	unsigned int	m_id;
	double			m_cost;
	double			m_vat;
};

#endif // !RECEIPT_H
