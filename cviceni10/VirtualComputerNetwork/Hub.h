#pragma once
#ifndef _HUB_H
#define _HUB_H

#include "Network.h"

struct Hub : public ANetworkElement {
public:
	Hub(int size);
	~Hub();
	void Connect(ANetworkElement* element) override;
	void Process() override;

private:
	void processIncomingMessages(MessagePort msgPort) override;

	ANetworkElement** m_connectedElements;
	int m_maximumConnectedElements;
	Queue<Message*> m_processedMessages;

	int m_counter;
};

#endif // !_HUB_H