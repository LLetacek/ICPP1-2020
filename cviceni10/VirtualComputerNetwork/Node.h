#pragma once
#ifndef _NODE_H
#define _NODE_H

#include "Network.h"

struct Node : public ANetworkElement {
public:
	Node(string address);
	~Node();
	void Connect(ANetworkElement* element) override;
	void Process() override;
	void PrepareMessageForSending(string target, string content);

private:
	void processIncomingMessages(MessagePort msgPort) override;

	string m_address;
	ANetworkElement* m_connectedElement;
	Queue<Message*> m_outgoingMessages;
	Queue<Message*> m_processedMessages;
};

#endif // !_NODE_H