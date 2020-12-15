#include <iostream>
using namespace std;

#include "Hub.h"

Hub::Hub(int size) : m_maximumConnectedElements(size), m_counter(0) {
	if (size <= 0)
		throw invalid_argument("velikost musi byt vetsi nez 0");
	m_connectedElements = new ANetworkElement * [size] {nullptr};
}

Hub::~Hub() {
	delete[] m_connectedElements;
}

void Hub::Connect(ANetworkElement* element) {
	if (m_maximumConnectedElements == m_counter)
		throw invalid_argument("pole je jiz plne");
	m_connectedElements[m_counter++] = element;
}

void Hub::Process() {
	if (IncomingMessages.IsEmpty())
		return;

	IncomingMessages.Processing(this, (void (ANetworkElement::*) (MessagePort)) & Hub::processIncomingMessages);
	while (!IncomingMessages.IsEmpty()) {
		IncomingMessages.Remove();
	}
}

void Hub::processIncomingMessages(MessagePort msgPort) {
	if (m_processedMessages.Contains(msgPort.Packet))
		return;

	for (int i = 0; i < m_counter; ++i) {
		if (m_connectedElements[i] != nullptr && m_connectedElements[i] != msgPort.Port) {
			(m_connectedElements[i])->InsertMessage(msgPort.Packet, this);
		}
	}
	m_processedMessages.Insert(msgPort.Packet);
}