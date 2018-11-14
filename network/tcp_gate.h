// Purpose: Tcp gate class for network
// Created: 2018.11.14
// By: CasinoHe

#pragma once

#ifndef SIMPLE_SERVER_NETWORK_TCP_GATE_H
#define SIMPLE_SERVER_NETWORK_TCP_GATE_H

#include "network/gate_base.h"
#include "log/log.h"

#include <string>

#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>

namespace simple_server {
	class CTcpGate: public CGateBase {
		public:
			CTcpGate() = delete;
			CTcpGate(const std::string ip, const unsigned int port);
			CTcpGate(const CTcpGate &) = delete;
			CTcpGate &operator=(CTcpGate &) = delete;

		private:
			virtual bool bind() override;
			virtual void listen() override;
			void do_accept(boost::asio::ip::tcp::endpoint endpoint, boost::asio::ip::tcp::socket socket);

			CLogManager logger;

		private:
			boost::shared_ptr<boost::asio::ip::tcp::endpoint> m_endpoint;
			boost::shared_ptr<boost::asio::ip::tcp::acceptor> m_acceptor;
	};
}

#endif
