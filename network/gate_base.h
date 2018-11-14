// Purpose: Abstract class gate base for network
// Created: 2018.11.14
// By: CasinoHe

#pragma once

#ifndef SIMPLE_SERVER_NETWORK_GATE_BASE_H
#define SIMPLE_SERVER_NETWORK_GATE_BASE_H

#include <string>

namespace simple_server{
	class CGateBase {
		public:
			CGateBase(int proto);
			CGateBase(CGateBase &gate) = delete;

			virtual void initialize(const std::string &ip, const unsigned short port);

		private:
			virtual void bind() = 0;
			virtual void listen() = 0;

		private:
			const int m_proto;  // tcp or udp
			std::string m_ip;
			unsigned short m_port;
	};
}

#endif
