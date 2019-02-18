// Purpose: Tcp gate implement
// Create: 2018.11.14
// By: CasinoHe

#include "network/tcp_gate.h"
#include "object/object_helper.h"
#include "object/connection/connection_object.h"

#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/bind.hpp>


namespace simple_server {
	namespace asio = boost::asio;
	CTcpGate::CTcpGate(const std::string ip, const unsigned int port): 
		CGateBase(1),
		logger("tcp_gate") {

		initialize(ip, port);
		if (!bind()) {
			return;
		}

		listen();
	}

	bool CTcpGate::bind() {
		boost::system::error_code err;
		asio::ip::address ip_address = asio::ip::make_address(m_ip, err);
		if (err) {
			LOG_ERROR(logger) << "Cannot bind address " << m_ip;
			return false;
		} 

		m_endpoint = boost::make_shared<asio::ip::tcp::endpoint>(ip_address, m_port);
		m_acceptor = boost::make_shared<asio::ip::tcp::acceptor>(io_context, *m_endpoint);
		return true;
	}

	void CTcpGate::listen() {
		asio::ip::tcp::endpoint peer_endpoint;
		m_acceptor->async_accept(
				peer_endpoint,
				[this, peer_endpoint] (boost::system::error_code ec, asio::ip::tcp::socket socket) {
				if (ec) {
					LOG_ERROR(logger) << "Accept socket failed.Message: " << ec.message();
					listen();
					return;
				}

				listen();
				do_accept(std::move(peer_endpoint), std::move(socket));
				return;
			});
	}

	void CTcpGate::do_accept(asio::ip::tcp::endpoint peer_endpoint, asio::ip::tcp::socket socket) {
		LOG_INFO(logger) << "TCP gate receives new connection: " << peer_endpoint.address() << " port:" << peer_endpoint.port();

		boost::shared_ptr<CConnectionObject> conn_object_ptr = CObjectHelper::create_object<CConnectionObject>("Connection");
		LOG_INFO(logger) << "Construct connection object, object_id is : " << conn_object_ptr->get_object_id();
	}
}