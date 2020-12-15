#include <iostream>
using namespace std;

#include "Node.h"

Node::Node(string address)
	: m_address(address), m_connectedElement(nullptr) {
}

Node::~Node() {
	while (!m_processedMessages.IsEmpty()) {
		Message* msg = m_processedMessages.Remove();
		if (!m_processedMessages.Contains(msg))
			delete msg;
	}
}

inline void Node::Connect(ANetworkElement* element) {
	m_connectedElement = element;
}

void Node::processIncomingMessages(MessagePort msgPort) {
	if ((msgPort.Packet->AddrTarget).compare(m_address) == 0) {
		cout << m_address << " prijal zpravu: \n\tid =>" << msgPort.Packet->Id
			 << "\n\tobsah => " << msgPort.Packet->Content
			 << "\n\tod => " << msgPort.Packet->AddrSource
			 << "\n\tdo => " << msgPort.Packet->AddrTarget << "\n\n";

		if ((msgPort.Packet->Content).compare("ping") == 0) {
			PrepareMessageForSending(msgPort.Packet->AddrSource, "pong");
		}

		m_processedMessages.Insert(msgPort.Packet);
	}
}

inline void Node::PrepareMessageForSending(string target, string content) {
	m_outgoingMessages.Insert(
		new Message{
			Network::NewId(),
			m_address,
			target,
			content
		}	);
}

void Node::Process() {
	if (!IncomingMessages.IsEmpty()) {
		IncomingMessages.Processing(this, (void (ANetworkElement::*) (MessagePort)) & Node::processIncomingMessages);
		while (!IncomingMessages.IsEmpty()) {
			IncomingMessages.Remove();
		}
	}

	if (!m_outgoingMessages.IsEmpty()) {
		if (m_connectedElement != nullptr)
			m_outgoingMessages.Processing(m_connectedElement, &ANetworkElement::InsertMessage);

		while (!m_outgoingMessages.IsEmpty()) {
			m_outgoingMessages.Remove();
		}
	}
}
