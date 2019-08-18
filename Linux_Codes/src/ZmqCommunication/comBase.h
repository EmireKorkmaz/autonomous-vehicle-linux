/**
 * \file        comBase.h
 * \brief       A brief description one line.
 *
 * \author      alperenbulut
 * \date        Aug 10, 2019
 */

#ifndef SRC_ZMQCOMMUNICATION_COMBASE_H_
#define SRC_ZMQCOMMUNICATION_COMBASE_H_

/*------------------------------< Includes >----------------------------------*/
#include <iostream>
#include <memory>
#include <zmq.hpp>
/*------------------------------< Defines >-----------------------------------*/

/*------------------------------< Typedefs >----------------------------------*/

/*------------------------------< Class  >------------------------------------*/
namespace zmqbase {

extern const std::string TCP_CONNECTION;
extern const std::string PROC_CONNECTION;

class ComBase;

enum PollEventType {
    NO = 0,
    POLLIN = ZMQ_POLLIN,
    POLLOUT = ZMQ_POLLOUT,
    POLLERR = ZMQ_POLLERR,
    POLLPRI = ZMQ_POLLPRI
};

struct PollItem {
    ComBase* base;
    PollEventType events;
    PollEventType revents;
};

class ComBase {
public:
    ComBase(int s_type, bool is_server = false);
    virtual ~ComBase() = 0;
    virtual void connect(const std::string& addr);

    void disconnect();
    std::string addr;

protected:
    int poll(PollItem& data, int timeout);

    std::shared_ptr<zmq::context_t> m_context;
    std::shared_ptr<zmq::socket_t> m_socket;
    bool m_is_server;
};
}

#endif /* SRC_ZMQCOMMUNICATION_COMBASE_H_ */
