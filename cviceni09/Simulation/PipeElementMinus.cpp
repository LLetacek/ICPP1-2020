#include "PipeElement.h"
#include <iostream>

PipeElementMinus::PipeElementMinus(int x, int y, IPipe* pipe) {
	if (x < 0 || pipe->GetSize() <= x || y < 0 || pipe->GetSize() <= y)
		throw std::invalid_argument("jste mimo pole");

	m_x = x;
	m_y = y;
	pipe->SetElement(this);
}

PipeElementMinus::~PipeElementMinus() {}

bool PipeElementMinus::IsConnectedCorrectly(const IPipe* pipe) const {
	if(pipe == nullptr)
		return false;

	if (m_x == (pipe->GetSize() - 1) || m_x == 0)
		return false;

    if (dynamic_cast<const PipeElementI*>(pipe->GetElement(m_x - 1, m_y)) || 
		pipe->GetElement(m_x - 1, m_y) == nullptr) {
		return false;
	}

	if (dynamic_cast<const PipeElementI*>(pipe->GetElement(m_x + 1, m_y)) ||
		pipe->GetElement(m_x + 1, m_y) == nullptr) {
		return false;
	}

	return true;
}