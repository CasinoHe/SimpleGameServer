// Purpose: Handle program starting options
// Created: 2018.11.7
// By: CasinoHe

#include "config/options.h"

#include <iostream>
#include <exception>

using namespace boost::program_options;

namespace simple_server{

	COptionsManager::COptionsManager() noexcept:
		m_desc("Allowed options") {

			m_desc.add_options()
				("help", "display help message")
				("test", value<bool>()->default_value(false))
				("config", value<std::string>()->default_value("config.json"));
	}

	bool COptionsManager::initialize_argument(int argc, const char **argv) {
			try {
				store(parse_command_line(argc, argv, m_desc), m_values_map);
				notify(m_values_map);
				return true;
			} catch (std::exception &e) {
				std::cout << "Invalid argument!" << std::endl << std::endl;
				help();
				return false;
			}
	}

	void COptionsManager::help() {
		std::cout << m_desc << std::endl;
	}

	std::string COptionsManager::get_config_filepath() {
		if (m_values_map.count("config") <= 0) {
			return "";
		}

		std::string filepath(m_values_map["config"].as<std::string>());
		return filepath;
	}

	bool COptionsManager::is_test() {
		if (m_values_map.count("test") <= 0) {
			return false;
		}

		return m_values_map["test"].as<bool>();
	}
}
