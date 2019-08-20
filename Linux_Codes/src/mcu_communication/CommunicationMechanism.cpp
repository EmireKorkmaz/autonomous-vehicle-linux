/**
 * \file        CommunicationMechanism.cpp
 * \brief       A brief description one line.
 *
 * \author      Sevval MEHDER
 * \date        Aug 17, 2019
 */

/*------------------------------< Includes >----------------------------------*/
#include "process.pb.h"
#include <iostream>
#include "CommunicationMechanism.h"
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/syslog_sink.h>

/*------------------------------< Defines >-----------------------------------*/

/*------------------------------< Typedefs >----------------------------------*/

/*------------------------------< Namespaces >--------------------------------*/

CommunicationMechanism::CommunicationMechanism() : zmq_listener_thread(&CommunicationMechanism::zmq_listener_task, this),
												   uart_periodic_req_thread(&CommunicationMechanism::uart_periodic_req_task, this),
												   publisher(false),
												   subscriber(false)
{
	m_logger = spdlog::stdout_color_mt("CommunicationMechanism");
	m_logger->set_level(spdlog::level::debug);
	// Constructor code
}

void CommunicationMechanism::zmq_listener_task()
{
	subscriber.subscribe("");

	std::string addr;
	addr.resize(50);
	// sprintf(&addr.front(), zmqbase::TCP_CONNECTION.c_str(), ipNum.c_str(), portNumSub);
	m_logger->info("Subscriber addr:{}", addr);
	std::string topic, msg;
	uart::pub_sub pubsub;
	while (true)
	{
		subscriber.recv(topic, msg);
		if (topic == "control/steering")
		{
			pubsub.ParseFromArray(msg.data(), msg.size());
			if (pubsub.msg_type() == uart::pub_sub_message::STEERING_MSG)
			{
			}
		}
		else if (topic == "control/throttle")
		{
			pubsub.ParseFromArray(msg.data(), msg.size());
			if (pubsub.msg_type() == uart::pub_sub_message::THROTTLE_MSG)
			{
			}
		}
		else if (topic == "control/brake")
		{
			pubsub.ParseFromArray(msg.data(), msg.size());
			if (pubsub.msg_type() == uart::pub_sub_message::BRAKE_MSG)
			{
			}
		}
		else if (topic == "control/startstop")
		{
			pubsub.ParseFromArray(msg.data(), msg.size());
			if (pubsub.msg_type() == uart::pub_sub_message::START_STOP_MSG)
			{
			}
		}
		else if (topic == "info/stateworking")
		{
			pubsub.ParseFromArray(msg.data(), msg.size());
			if (pubsub.msg_type() == uart::pub_sub_message::STATE_WORKING_MSG)
			{
			}
		}
		else if (topic == "info/hcsr04")
		{
			pubsub.ParseFromArray(msg.data(), msg.size());
			if (pubsub.msg_type() == uart::pub_sub_message::HCSR4_MSG)
			{
			}
		}
		else if (topic == "info/gps")
		{
			pubsub.ParseFromArray(msg.data(), msg.size());
			if (pubsub.msg_type() == uart::pub_sub_message::GPS_MSG)
			{
			}
		}
		else
		{
			m_logger->critical("Invalid Topic: {}", topic);
		}
	}
}

void CommunicationMechanism::uart_periodic_req_task()
{

	while (true)
		;
}

void CommunicationMechanism::waitUntilFinish()
{

	// Join the thread with the main thread
	this->zmq_listener_thread.join();
	this->uart_periodic_req_thread.join();
}

/*--------------------------< Parse Functions >--------------------------*/
bool parse_startstop_req(std::string &req, uart::startstop_enum &status)
{

	uart::pub_sub pubsub;
	if (pubsub.ParseFromArray(req.data(), req.size()))
	{
		if (pubsub.has_startstop())
		{
			status = pubsub.startstop().cmd();
			return true;
		}
	}

	return false;
}

bool parse_throttle_req(std::string &req, int &throttle)
{

	uart::pub_sub pubsub;
	if (pubsub.ParseFromArray(req.data(), req.size()))
	{
		if (pubsub.has_throttle())
		{
			throttle = pubsub.throttle().throttlevalue();
			return true;
		}
	}

	return false;
}
bool parse_steer_req(std::string &req, uart::steering_enum &cmd, double &angle)
{

	uart::pub_sub pubsub;
	if (pubsub.ParseFromArray(req.data(), req.size()))
	{
		if (pubsub.has_steering())
		{
			cmd = pubsub.steering().cmd();
			angle = pubsub.steering().angle();
			return true;
		}
	}

	return false;
}

bool parse_break_req(std::string &req, bool &is_break)
{

	uart::pub_sub pubsub;
	if (pubsub.ParseFromArray(req.data(), req.size()))
	{
		if (pubsub.has_brake())
		{
			is_break = pubsub.brake().brakevalue();
			return true;
		}
	}

	return false;
}
bool parse_stateworking(std::string &req, uart::stateWorking_enum &cmd)
{

	uart::pub_sub pubsub;
	if (pubsub.ParseFromArray(req.data(), req.size()))
	{
		if (pubsub.has_statework())
		{
			cmd = pubsub.statework().cmd();
			return true;
		}
	}

	return false;
}
bool parse_hcsr4(std::string &req, double &distance)
{

	uart::pub_sub pubsub;
	if (pubsub.ParseFromArray(req.data(), req.size()))
	{
		if (pubsub.has_hcsr4_dis())
		{
			distance = pubsub.hcsr4_dis().distance();
			return true;
		}
	}

	return false;
}
bool parse_gps(std::string &req, float &latitude, float &longitude)
{

	uart::pub_sub pubsub;
	if (pubsub.ParseFromArray(req.data(), req.size()))
	{
		if (pubsub.has_location())
		{
			latitude = pubsub.location().latitude();
			longitude = pubsub.location().longitude();
			return true;
		}
	}

	return false;
}
