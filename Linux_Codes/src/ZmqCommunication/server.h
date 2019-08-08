#ifndef SERVER_H
#define SERVER_H

#include "comBase.h"

namespace ZMQCommunication {

class Server : public ComBase {
public:
    // constructor that takes a boolean paramater checks whether it is server or
    // not
    Server();
    ~Server();
    bool recv(zmq::message_t& msg, long timeout = -1);
    bool send(const zmq::message_t& msg);
};
}

#endif
