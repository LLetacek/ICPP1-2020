#include "Receipt.h"

Receipt::Receipt(int id, double cost, double vat) : m_id(id),
													m_cost(cost),
													m_vat(vat) {
}

Receipt::Receipt() : m_cost(0),
					 m_vat(0) {
}

Receipt::~Receipt() {
}

void Receipt::setId(int id) {
	m_id = id;
}

void Receipt::setCost(double cost) {
	m_cost = cost;
}

void Receipt::setVat(double vat) {
	m_vat = vat;
}

int Receipt::getId() const {
	return m_id;
}

double Receipt::getCost() const {
	return m_cost;
}

double Receipt::getVat() const {
	return m_vat;
}
