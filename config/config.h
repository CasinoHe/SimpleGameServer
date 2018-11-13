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
			template<typename T> T get_value(const std::string key) const;
			template<typename T> bool find_value(const std::string key) const;
		private:
			boost::property_tree::ptree m_ptree;
			boost::filesystem::path m_filepath;
			CLogManager logger;
	};

	template<typename T>
	T CConfigManager::get_value(const std::string key) const {
		// need to do find_value first!
		T value = m_ptree.get<T>(key);
		return value;
	}

	template<typename T>
	bool CConfigManager::find_value(const std::string key) const {
		try {
			T value = m_ptree.get<T>(key);
		} catch (boost::property_tree::ptree_bad_path e) {
			return false;
		} catch (boost::property_tree::ptree_bad_data e) {
			return false;
		} catch (std::exception e) {
			return false;
		}

		return true;
	}
}


#endif
