// Purpose: Gate base implement
// Created: 2018.11.14
// By: CasinoHe

#include "network/gate_base.h"

#include <boost/asio.hpp>

namespace simple_server {
	boost::asio::io_context io_context;

	CGateBase::CGateBase(int proto):
		m_proto(proto) {
	}

	void CGateBase::initialize(const std::string &ip, const unsigned short port) {
		m_ip = ip;
		m_port = port;
	}
}
