// Purpose: Tcp gate class for network
// Created: 2018.11.14
// By: CasinoHe

#pragma once

#ifndef SIMPLE_SERVER_NETWORK_TCP_GATE_H
#define SIMPLE_SERVER_NETWORK_TCP_GATE_H

#include "network/gate_base.h"

#include <string>

namespace simple_server {
	class CTcpGate: public CGateBase {
		public:
			CTcpGate() = delete;
			CTcpGate(const std::string ip, const unsigned int port);
			CTcpGate(const CTcpGate &) = delete;
			CTcpGate &operator=(CTcpGate &) = delete;

		private:
			virtual void bind() override;
			virtual void listen() override;
	};
}

#endif
