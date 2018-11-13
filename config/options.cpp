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
				("test", value<bool>()->default_value(false), "start unit test, false or true")
				("config_file", value<std::string>()->default_value("config.json"), "server config file path")
				("config_key", value<std::string>()->default_value("game"), "server config dict key in config file, default is \"game\"");
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
		if (m_values_map.count("config_file") <= 0) {
			return "";
		}

		std::string filepath(m_values_map["config_file"].as<std::string>());
		return filepath;
	}

	bool COptionsManager::is_test() const {
		if (m_values_map.count("test") <= 0) {
			return false;
		}

		return m_values_map["test"].as<bool>();
	}

	bool COptionsManager::need_help() const {
		if (m_values_map.count("help") <= 0) {
			return false;
		}
		return true;
	}

	std::string COptionsManager::get_config_key() {
		if (m_values_map.count("config_key") <= 0) {
			return "";
		} else {
			return m_values_map["config_key"].as<std::string>();
		}
	}
}
