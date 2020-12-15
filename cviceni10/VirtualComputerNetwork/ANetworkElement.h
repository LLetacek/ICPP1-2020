#pragma once
#ifndef _A_NETWORK_ELEMENT_H
#define _A_NETWORK_ELEMENT_H

struct ANetworkElement {
public:
	virtual ~ANetworkElement() {}
	void InsertMessage(Message* message, ANetworkElement* port);
	void InsertMessage(Message* message);
	virtual void Process() = 0;
	virtual void Connect(ANetworkElement* element) = 0;

protected:
	virtual void processIncomingMessages(MessagePort msgPort) = 0;

	Queue<MessagePort> IncomingMessages;
};

inline void ANetworkElement::InsertMessage(Message* message, ANetworkElement* port) {
	IncomingMessages.Insert(MessagePort{ message, port });
}

inline void ANetworkElement::InsertMessage(Message* message) {
	IncomingMessages.Insert(MessagePort{ message, this });
}

#endif // !_A_NETWORK_ELEMENT_H