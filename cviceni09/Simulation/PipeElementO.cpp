#include "PipeElement.h"
#include <iostream>

PipeElementO::PipeElementO(int x, int y, IPipe* pipe) {
	if (x < 0 || pipe->GetSize() <= x || y < 0 || pipe->GetSize() <= y)
		throw std::invalid_argument("jste mimo pole");

	m_x = x;
	m_y = y;
	pipe->SetElement(this);
}

PipeElementO::~PipeElementO() {}

bool PipeElementO::IsConnectedCorrectly(const IPipe* pipe) const {
	return (pipe != nullptr);
}