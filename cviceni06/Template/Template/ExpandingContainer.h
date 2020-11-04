#pragma once
#ifndef _EXPANDING_CONTAINER_H
#define _EXPANDING_CONTAINER_H

#include <iostream>

template<typename DataType, unsigned InitSize = 5, unsigned IncreasingCoefficient = 2>
class ExpandingContainer {
 public:
	 ExpandingContainer();
	 ~ExpandingContainer();
	 void Add(const DataType& o);
	 DataType& operator[](int index);
	 DataType operator[](int index) const;
	 unsigned int Size() const;
	 void AddTo(int index, const DataType& o);
	 void Remove(int index);
 private:
	 bool IsFreePlaceInArray() const;
	 void ExtendArray();

	 unsigned int  m_arraySize;
	 DataType* m_array;
	 unsigned int  m_validElementsCounter;
};

template<typename DataType, unsigned InitSize, unsigned IncreasingCoefficient>
ExpandingContainer<DataType, InitSize, IncreasingCoefficient>::ExpandingContainer()
	: m_arraySize((InitSize != 0) ? InitSize : throw std::invalid_argument("init velikost nesmi byt 0")),
	  m_array(nullptr),
	  m_validElementsCounter(0) 
{
	if (IncreasingCoefficient <= 1)
		throw std::invalid_argument("koeficient musi byt vetsi nez 1");

	m_array = new DataType[m_arraySize];
}

template<typename DataType, unsigned InitSize, unsigned IncreasingCoefficient>
ExpandingContainer<DataType, InitSize, IncreasingCoefficient>::~ExpandingContainer() {
	delete[] m_array;
}

template<typename DataType, unsigned InitSize, unsigned IncreasingCoefficient>
bool ExpandingContainer<DataType, InitSize, IncreasingCoefficient>::IsFreePlaceInArray() const {
	return m_validElementsCounter < m_arraySize;
}

template<typename DataType, unsigned InitSize, unsigned IncreasingCoefficient>
void ExpandingContainer<DataType, InitSize, IncreasingCoefficient>::ExtendArray() {
	m_arraySize *= IncreasingCoefficient;
	DataType* newArray = new DataType[m_arraySize];
	for (unsigned int i = 0; i < m_validElementsCounter; i++) {
		newArray[i] = m_array[i];
	}

	DataType* tmp = m_array;
	m_array = newArray;
	delete[] tmp;
}

template<typename DataType, unsigned InitSize, unsigned IncreasingCoefficient>
void ExpandingContainer<DataType, InitSize, IncreasingCoefficient>::Add(const DataType& o) {
	if (!IsFreePlaceInArray())
		ExtendArray();
	m_array[m_validElementsCounter++] = o;
}

template<typename DataType, unsigned InitSize, unsigned IncreasingCoefficient>
DataType& ExpandingContainer<DataType, InitSize, IncreasingCoefficient>::operator[](int index) {
	if(index < 0 || (unsigned int)index >= m_validElementsCounter)
		throw std::invalid_argument("sahate mimo indexy, kde jsou prvky ulozeny");
	return m_array[index];
}

template<typename DataType, unsigned InitSize, unsigned IncreasingCoefficient>
DataType ExpandingContainer<DataType, InitSize, IncreasingCoefficient>::operator[](int index) const {
	if (index < 0 || (unsigned int)index >= m_validElementsCounter)
		throw std::invalid_argument("sahate mimo indexy, kde jsou prvky ulozeny");
	return m_array[index];
}

template<typename DataType, unsigned InitSize, unsigned IncreasingCoefficient>
unsigned int ExpandingContainer<DataType, InitSize, IncreasingCoefficient>::Size() const {
	return m_validElementsCounter;
}

template<typename DataType, unsigned InitSize, unsigned IncreasingCoefficient>
void ExpandingContainer<DataType, InitSize, IncreasingCoefficient>::AddTo(int index, const DataType& o) {
	if (index < 0 || (unsigned int)index >= (m_validElementsCounter + 1))
		throw std::invalid_argument("nemuzete vlozit na tento index, prvky by nebyly spojite");

	if (index == (m_validElementsCounter + 1) - 1) {
		Add(o);
		return;
	}
	
	if (!IsFreePlaceInArray())
		ExtendArray();

	m_validElementsCounter++;
	for (int i = (m_validElementsCounter - 1); i >= (index + 1); i--) {
		m_array[i] = m_array[i-1];
	}
	m_array[index] = o;
}

template<typename DataType, unsigned InitSize, unsigned IncreasingCoefficient>
void ExpandingContainer<DataType, InitSize, IncreasingCoefficient>::Remove(int index) {
	if (index < 0 || (unsigned int)index >= m_validElementsCounter)
		throw std::invalid_argument("prvek na tomto indexu neexistuje");

	for (unsigned int i = index ; i < (m_validElementsCounter - 1); i++) {
		m_array[i] = m_array[i+1];
	}
	m_validElementsCounter--;
}

#endif // !_EXPANDING_CONTAINER_H