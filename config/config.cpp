// Purpose: Parse and Handle server configuration
// Created: 2018.11.7
// By: CasinoHe

#include "config/config.h"

namespace simple_server {
	CConfigManager::CConfigManager(std::string filename):
		m_filepath(filename) {
	}
}
