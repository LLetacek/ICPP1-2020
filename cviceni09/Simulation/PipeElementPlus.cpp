#include "PipeElement.h"
#include <iostream>

PipeElementPlus::PipeElementPlus(int x, int y, IPipe* pipe) {
	if (x < 0 || pipe->GetSize() <= x || y < 0 || pipe->GetSize() <= y)
		throw std::invalid_argument("jste mimo pole");

	m_x = x;
	m_y = y;
	pipe->SetElement(this);
}

PipeElementPlus::~PipeElementPlus() {}

bool PipeElementPlus::IsConnectedCorrectly(const IPipe* pipe) const {
	if (pipe == nullptr)
		return false;

	if (m_x == (pipe->GetSize() - 1) || m_x == 0 || m_y == (pipe->GetSize() - 1) || m_y == 0)
		return false;

	if (pipe->GetElement(m_x - 1, m_y) == nullptr || pipe->GetElement(m_x + 1, m_y) == nullptr ||
		pipe->GetElement(m_x, m_y - 1) == nullptr || pipe->GetElement(m_x, m_y + 1) == nullptr) {
		return false;
	}

	if (dynamic_cast<const PipeElementI*>(pipe->GetElement(m_x - 1, m_y)) || 
		dynamic_cast<const PipeElementI*>(pipe->GetElement(m_x + 1, m_y))) {
		return false;
	}

	if (dynamic_cast<const PipeElementMinus*>(pipe->GetElement(m_x, m_y - 1)) ||
		dynamic_cast<const PipeElementMinus*>(pipe->GetElement(m_x, m_y + 1))) {
		return false;
	}

	return (dynamic_cast<const PipeElementT*>(pipe->GetElement(m_x, m_y + 1)) == nullptr);
}