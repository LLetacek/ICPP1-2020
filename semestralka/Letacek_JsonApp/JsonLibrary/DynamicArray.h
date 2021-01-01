#ifndef __DYNAMIC_ARRAY_H
#define __DYNAMIC_ARRAY_H

#include <string>
#include <iostream>

// - šablona s parametrem datového typu uložených hodnot
// - není povoleno užití STL kontejnerù ani jiných knihoven pro ukládání dat
// - realizace musí využívat dynamicky alokované pole, spojový seznam nebo jinou vhodnou Vámi implementovanou ADS 
template<typename T>
class DynamicArray {
public:
	DynamicArray();
	DynamicArray(const DynamicArray& cpy);
	~DynamicArray();

	// - pøidá element na konec pole
	void append(const T& element);

	// - výjimky pøi neplatném nebo nekorektním indexu
	const T& getElementAt(int index) const;
	T& getElementAt(int index);

	// - vrací velikost (poèet prvkù) v poli
	int getSize() const;

	template <class E>
	std::string serializeAll(std::string(E::* f) () const) const;

	template <class E>
	const T& findByKey(bool (E::* f) (std::string) const, const std::string key) const;

	// - odstrani posledni prvek ze seznamu
	T remove();

private:
	struct Container {
		T element;
		Container* next;
		Container* previous;
	};

	Container* m_first;
	Container* m_last;
	int m_counter;
};

template<typename T>
DynamicArray<T>::DynamicArray()
	: m_first(nullptr), m_last(nullptr), m_counter(0) {
}

template<typename T>
DynamicArray<T>::DynamicArray(const DynamicArray& cpy)
	: m_first(nullptr), m_last(nullptr), m_counter(0) {
	Container* tmp = cpy.m_first;
	while (tmp) {
		append(tmp->element);
		tmp = tmp->next;
	}
}

template<typename T>
DynamicArray<T>::~DynamicArray() {
	while (m_first) {
		Container* tmp = m_first;
		m_first = m_first->next;
		delete tmp;
	}
}

template<typename T>
void DynamicArray<T>::append(const T& element) {
	m_last = new Container{ element, nullptr, m_last };

	if (!m_first)
		m_first = m_last;
	else
		m_last->previous->next = m_last;

	++m_counter;
}

template<typename T>
const T& DynamicArray<T>::getElementAt(int index) const {
	if (m_counter < 0)
		throw std::invalid_argument("Index musi byt vetsi nebo roven nule!");
	else if (m_counter <= index)
		throw std::out_of_range("Jste indexem mimo pole!");

	// - rychlejsi prohledavani, byt slozitostne porad linearni.
	// -- (0 -1), resp. (m_counter) nastavuji kvuli inkrementaci, resp. dekrementaci pred overenim shody s indexem.
	// --- indexace od 0.
	Container* tmp = nullptr;
	int mid = (m_counter / 2);
	int tmpCounter = (index < mid) ? (0 - 1) : (m_counter);
	while (true) {
		if (index < mid) {
			tmp = (!tmp) ? m_first : tmp->next;
			++tmpCounter;
		}
		else {
			tmp = (!tmp) ? m_last : tmp->previous;
			--tmpCounter;
		}

		if (tmpCounter == index)
			return tmp->element;
	}
}

template<typename T>
inline T& DynamicArray<T>::getElementAt(int index) {
	// aby nebyla duplicita - inspirace: Scott Meyers
	const DynamicArray& constMe = *this;
	return const_cast<T&>(constMe.getElementAt(index));
}

template<typename T>
inline int DynamicArray<T>::getSize() const {
	return m_counter;
}

template<typename T>
template <class E>
inline std::string DynamicArray<T>::serializeAll(std::string(E::* f) () const) const {
	std::string serializer = "";
	Container* tmp = m_first;
	while (tmp) {
		serializer += std::invoke(f, (tmp->element));
		tmp = tmp->next;
		if (tmp)
			serializer += ", ";
	}
	return serializer;
}

template<typename T>
template <class E>
inline const T& DynamicArray<T>::findByKey(bool (E::* f) (std::string) const, const std::string key) const {
	Container* tmp = m_first;
	while (tmp) {
		if(std::invoke(f, (tmp->element), key)==true)
			return tmp->element;
		tmp = tmp->next;
	}
	throw std::invalid_argument("Prvek vami urcenym klicem nebyl nalezen!");
}

template<typename T>
inline T DynamicArray<T>::remove() {
	if (!m_first)
		throw std::out_of_range("Pole je prazdne");

	T element = m_first->element;
	Container* tmp = m_first;
	if (m_first->next) {
		m_first = m_first->next;
		m_first->previous = nullptr;
	} 
	else {
		m_first = nullptr;
		m_last = nullptr;
	}

	--m_counter;
	delete tmp;
	return element;
}

#endif // !__DYNAMIC_ARRAY_H