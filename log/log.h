// Purpose: Log handler
// Created: 2018.11.5
// By: CasinoHe

#pragma once
#ifndef SIMPLE_SERVER_LOG_LOG_H
#define SIMPLE_SERVER_LOG_LOG_H

#include <string>
#include <ostream>

#include <boost/log/trivial.hpp>

#define LOG_TRACE (boost::log::trivial::trace)
#define LOG_DEBUG (boost::log::trivial::debug)
#define LOG_INFO (boost::log::trivial::info)
#define LOG_WARNING (boost::log::trivial::warning)
#define LOG_ERROR (boost::log::trivial::error)
#define LOG_FATAL (boost::log::trivial::fatal)

namespace simple_server {
	class CLogManager {
		public:
			typedef boost::log::sources::severity_logger<boost::log::trivial::severity_level> LOGGER_TYPE;

		public:
			CLogManager(const std::string filename);
			CLogManager(const char *filename);
			inline LOGGER_TYPE get_logger() {return m_logger;}
			inline boost::log::trivial::severity_level get_level() {return m_level;}
			inline void set_level(const boost::log::trivial::severity_level level) {m_level = level;}

			void trace(const char *msg);
			void info(const char *msg);
			void debug(const char *msg);
			void warning(const char *msg);
			void error(const char *msg);
			void fatal(const char *msg);

			friend CLogManager &operator<<(CLogManager &logger, const char *msg);
			friend CLogManager &operator<<(CLogManager &logger, const boost::log::trivial::severity_level &level);
			CLogManager &operator()(const boost::log::trivial::severity_level &level);

		private:
			void initialize();

			std::string m_filename;
			LOGGER_TYPE m_logger;
			boost::log::trivial::severity_level m_level;
	};

	extern CLogManager g_logger;
}

#endif
