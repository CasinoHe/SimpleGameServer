// Purpose: Parse and Handle server configuration
// Created: 2018.11.7
// By: CasinoHe

#include "log/log.h"
#include "config/config.h"

#include <stdexcept>

#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/exceptions.hpp>

namespace pt = boost::property_tree;

namespace simple_server {
	CConfigManager::CConfigManager(std::string filename):
		m_filepath(filename),
		logger("config") {
	}

	bool CConfigManager::parse_config() {
		if (!boost::filesystem::exists(m_filepath)) {
			LOG_FATAL(logger) << "Cannot find config file: " << m_filepath.c_str();
			return false;
		}

		if (!boost::filesystem::is_regular(m_filepath)) {
			LOG_FATAL(logger) << "File : " << m_filepath.c_str() << " is not a regular file";
			return false;
		}

		try {
			pt::read_json(m_filepath.string(), m_ptree);
		} catch (std::exception &e) {
			LOG_FATAL(logger) << "Parse config file: " << m_filepath << " failed.";
			return false;
		}

		return true;
	}
}
