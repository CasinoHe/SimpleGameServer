// Purpose: Abstract class gate base for network
// Created: 2018.11.14
// By: CasinoHe

#pragma once

#ifndef SIMPLE_SERVER_NETWORK_GATE_BASE_H
#define SIMPLE_SERVER_NETWORK_GATE_BASE_H

#include <string>
#include <boost/asio.hpp>

namespace simple_server{
	extern boost::asio::io_context io_context;

	class CGateBase {
		public:
			CGateBase(int proto);
			CGateBase(CGateBase &gate) = delete;

			virtual void initialize(const std::string &ip, const unsigned short port);

		protected:
			virtual bool bind() = 0;
			virtual void listen() = 0;

		protected:
			const int m_proto;  // tcp or udp
			std::string m_ip;
			unsigned short m_port;
	};

}

#endif
