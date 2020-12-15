#pragma once
#ifndef _MESSAGE_H
#define _MESSAGE_H

struct ANetworkElement;

struct Message {
    int Id;
    string AddrSource;
    string AddrTarget;
    string Content;

    Message(int id, string addrSource, string addrTarget, string content)
        : Id(id),
          AddrSource(addrSource),
          AddrTarget(addrTarget),
          Content(content) {
    }
};

struct MessagePort {
    Message* Packet;
    ANetworkElement* Port;

    MessagePort(Message* message, ANetworkElement* port)
        : Packet(message),
          Port(port) {
    }

    bool operator==(const MessagePort& msgPrt) const {
        return (Packet->Id == msgPrt.Packet->Id);
    }
};

#endif // !_MESSAGE_H