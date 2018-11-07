// Purpose: Handle program starting options
// Created: 2018.11.7
// By: CasinoHe

#pragma once

#ifndef SIMPLE_SERVER_CONFIG_OPTIONS_H
#define SIMPLE_SERVER_CONFIG_OPTIONS_H

#include <string>

#include <boost/program_options.hpp>

namespace simple_server {
	class COptionsManager {
		public:
			COptionsManager() noexcept;
			COptionsManager(const COptionsManager &) = delete;
			bool initialize_argument(int argc, const char **argv);
			std::string get_config_filepath();
			bool is_test();
		private:
			void help();
		private:
			boost::program_options::options_description m_desc;
			boost::program_options::variables_map m_values_map;
	};
}

#endif
