#include <iostream>
using namespace std;

#include "Network.h"

int Network::m_idMessageCounter = 0;

Network::Network() {}

Network::~Network() {
	while (!m_networkElements.IsEmpty()) {
		ANetworkElement* element = m_networkElements.Remove();
		if(!m_networkElements.Contains(element))
			delete element;
	}
}