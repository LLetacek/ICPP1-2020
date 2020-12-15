#include "PipeElement.h"
#include <iostream>

PipeElementI::PipeElementI(int x, int y, IPipe* pipe) {
	if (x < 0 || pipe->GetSize() <= x || y < 0 || pipe->GetSize() <= y)
		throw std::invalid_argument("jste mimo pole");

	m_x = x;
	m_y = y;
	pipe->SetElement(this);
}

PipeElementI::~PipeElementI() {}

bool PipeElementI::IsConnectedCorrectly(const IPipe* pipe) const {
	if (m_y == (pipe->GetSize() - 1) || m_y == 0)
		return false;

	if (pipe->GetElement(m_x, m_y - 1) == nullptr || pipe->GetElement(m_x, m_y + 1) == nullptr) {
		return false;
	}

	if (dynamic_cast<const PipeElementMinus*>(pipe->GetElement(m_x, m_y - 1)) ||
		dynamic_cast<const PipeElementMinus*>(pipe->GetElement(m_x, m_y + 1))) {
		return false;
	}

	return (dynamic_cast<const PipeElementT*>(pipe->GetElement(m_x, m_y + 1)) == nullptr);
}