// Purpose: Gate base implement
// Created: 2018.11.14
// By: CasinoHe

#include "network/gate_base.h"


namespace simple_server {
	CGateBase::CGateBase(int proto):
		m_proto(proto) {
	}

	void CGateBase::initialize(const std::string &ip, const unsigned short port) {
		m_ip = ip;
		m_port = port;
	}
}
