// Purpose: Parse and Handle server configuration
// Created: 2018.11.7
// By: CasinoHe

#pragma once

#ifndef SIMPLE_SERVER_CONFIG_CONFIG_H
#define SIMPLE_SERVER_CONFIG_CONFIG_H

#include <string>

namespace simple_server {
	class CConfigManager {
		public:
			CConfigManager(std::string filename);
		private:
			std::string m_filepath;
	};
}


#endif
