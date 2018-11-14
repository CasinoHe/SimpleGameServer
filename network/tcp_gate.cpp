// Purpose: Tcp gate implement
// Create: 2018.11.14
// By: CasinoHe

#include "network/tcp_gate.h"

#include <boost/asio.hpp>

namespace simple_server {
	CTcpGate::CTcpGate(const std::string ip, const unsigned int port): 
		CGateBase(1) {
		initialize(ip, port);
	}

	void CTcpGate::bind() {
	}

	void CTcpGate::listen() {
	}
}
