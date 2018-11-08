// Purpose: Parse and Handle server configuration
// Created: 2018.11.7
// By: CasinoHe

#pragma once

#ifndef SIMPLE_SERVER_CONFIG_CONFIG_H
#define SIMPLE_SERVER_CONFIG_CONFIG_H

#include "log/log.h"

#include <string>

#include <boost/filesystem.hpp>
#include <boost/property_tree/ptree.hpp>

namespace simple_server {
	class CConfigManager {
		public:
			CConfigManager(std::string filename);

			bool parse_config();
		private:
			boost::property_tree::ptree m_ptree;
			boost::filesystem::path m_filepath;
			CLogManager logger;
	};
}


#endif
