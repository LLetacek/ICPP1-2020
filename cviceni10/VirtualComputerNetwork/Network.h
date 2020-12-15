#pragma once
#ifndef _NETWORK_H
#define _NETWORK_H

#include "Message.h"
#include "Queue.h"
#include "ANetworkElement.h"

struct Network {
public:
	Network();
	~Network();
	static int NewId();

	void ProcessAll();
	void Connect(ANetworkElement* element);

private:
	static int m_idMessageCounter;
	Queue<ANetworkElement*> m_networkElements;
};

inline int Network::NewId() {
	return m_idMessageCounter++;
}

inline void Network::ProcessAll() {
	m_networkElements.Processing(&ANetworkElement::Process);
}

inline void Network::Connect(ANetworkElement* element) {
	m_networkElements.Insert(element);
}

#endif // !_NETWORK_H