// Purpose: Log handler
// Created: 2018.11.5
// By: CasinoHe

#pragma once
#ifndef SIMPLE_SERVER_LOG_LOG_H
#define SIMPLE_SERVER_LOG_LOG_H

#include <string>
#include <ostream>

#include <boost/log/trivial.hpp>

namespace simple_server {
	class CLogManager {
		public:
			typedef boost::log::sources::severity_logger<boost::log::trivial::severity_level> LOGGER_TYPE;

		public:
			CLogManager(const std::string filename);
			CLogManager(const char *filename);
			inline LOGGER_TYPE get_logger() {return m_logger;}
			inline boost::log::trivial::severity_level get_level() {return m_level;}

			void trace(const char *msg);
			void info(const char *msg);
			void debug(const char *msg);
			void warning(const char *msg);
			void error(const char *msg);
			void fatal(const char *msg);

			friend CLogManager &operator<<(CLogManager &logger, const char *msg);

		private:
			void initialize();

			std::string m_filename;
			LOGGER_TYPE m_logger;
			boost::log::trivial::severity_level m_level;
	};

	extern CLogManager g_logger;
}

#endif
