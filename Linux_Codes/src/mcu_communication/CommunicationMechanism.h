/**
 * \file        CommunicationMechanism.h
 * \brief       A brief description one line.
 *
 * \author      Sevval MEHDER
 * \date        Aug 17, 2019
 */

#ifndef COM_MECHANISM_H
#define COM_MECHANISM_H

/*------------------------------< Includes >----------------------------------*/
#include "UARTCommunication.h"
#include "publisher.h"
#include "subscriber.h"
#include <thread>
#include <spdlog/spdlog.h>
/*------------------------------< Defines >-----------------------------------*/

/*------------------------------< Typedefs >----------------------------------*/

/*------------------------------< Class  >------------------------------------*/

class CommunicationMechanism
{
public:
    CommunicationMechanism(); /* Constructor */
    ~CommunicationMechanism();
    void waitUntilFinish();

private:
    void zmq_listener_task();
    void uart_periodic_req_task();

    std::thread zmq_listener_thread;
    std::thread uart_periodic_req_thread;
    std::shared_ptr<spdlog::logger> m_logger;
    pubsub::Publisher publisher;
    pubsub::Subscriber subscriber;
    //	UARTCommunication communication;
};

#endif /* COM_MECHANISM_H */
