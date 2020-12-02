#include "PipeElement.h"
#include <iostream>

Pipe::Pipe(int size)
	: m_size(size) {
	if (size <= 0)
		throw std::invalid_argument("velikost je 0");
	m_array = new PipeElement**[size];
	for (int i = 0; i < size; ++i) {
		m_array[i] = new PipeElement * [size] {nullptr};
	}
}

Pipe::~Pipe() {
	for (int i = 0; i < m_size; ++i) {
		for (int j = 0; j < m_size; ++j) {
			if (m_array[i][j] != nullptr) {
				delete m_array[i][j];
			}
		}
		delete[] m_array[i];
	}
	delete[] m_array;
}

const PipeElement* Pipe::GetElement(int x, int y) const {
	if(x < 0 || x >= m_size || y < 0 || y >= m_size )
		throw std::invalid_argument("jste mimo pole");

	return m_array[x][y];
}

bool Pipe::IsPipeOk() const {
	for (int i = 0; i < m_size; ++i) {
		for (int j = 0; j < m_size; ++j) {
			if (m_array[i][j] == nullptr)
				continue;
			if (!m_array[i][j]->IsConnectedCorrectly(this))
				return false;
		}
	}
	return true;
}

void Pipe::SetElement(PipeElement* element) {
	if (element == nullptr)
		return;

	if (m_array[element->m_x][element->m_y] != nullptr) {
		delete element;
		throw std::invalid_argument("vkladate na obsazene misto");
	}

	m_array[element->m_x][element->m_y] = element;
}

int Pipe::GetSize() const {
	return m_size;
}

