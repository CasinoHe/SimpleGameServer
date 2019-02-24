// Purpose: Log handler
// Created: 2018.11.5
// By: CasinoHe

#pragma once
#ifndef SIMPLE_SERVER_LOG_LOG_H
#define SIMPLE_SERVER_LOG_LOG_H

#include <string>
#include <ostream>

#include <boost/log/trivial.hpp>
#include <boost/log/attributes/attribute.hpp>
#include <boost/log/attributes/attribute_value.hpp>
#include <boost/log/attributes/attribute_value_impl.hpp>


namespace simple_server {
	class CLogManager {
		public:
			typedef boost::log::sources::severity_logger_mt<boost::log::trivial::severity_level> LOGGER_MT_TYPE;
			typedef boost::log::sources::severity_logger<boost::log::trivial::severity_level> LOGGER_TYPE;

		public:
			CLogManager(const std::string filename);
			CLogManager(const char *filename);
			inline LOGGER_MT_TYPE &get_logger() {return m_logger;}
			inline boost::log::trivial::severity_level get_level() {return m_level;}
			inline void set_level(const boost::log::trivial::severity_level level) {m_level = level;}

			friend CLogManager &operator<<(CLogManager &logger, const char *msg);
			friend CLogManager &operator<<(CLogManager &logger, const boost::log::trivial::severity_level &level);
			CLogManager &operator()(const boost::log::trivial::severity_level &level);

			static void initialize_log_sinks();
			static bool has_init;
		private:
			std::string m_filename;
			LOGGER_MT_TYPE m_logger;
			boost::log::trivial::severity_level m_level;

			virtual void init_logger();
	};

	// log attributes for filename and linenum

	extern CLogManager g_logger;
}

#define LOG_TRACE(logger) BOOST_LOG_SEV(logger.get_logger(), boost::log::trivial::trace) << "[" << BOOST_CURRENT_FUNCTION << ":" << __LINE__ << "] "
#define LOG_DEBUG(logger) BOOST_LOG_SEV(logger.get_logger(), boost::log::trivial::debug) << "[" << BOOST_CURRENT_FUNCTION << ":" << __LINE__ << "] "
#define LOG_INFO(logger) BOOST_LOG_SEV(logger.get_logger(), boost::log::trivial::info) << "[" << BOOST_CURRENT_FUNCTION << ":" << __LINE__ << "] "
#define LOG_WARNING(logger) BOOST_LOG_SEV(logger.get_logger(), boost::log::trivial::warning) << "[" << BOOST_CURRENT_FUNCTION << ":" << __LINE__ << "] "
#define LOG_ERROR(logger) BOOST_LOG_SEV(logger.get_logger(), boost::log::trivial::error) << "[" << BOOST_CURRENT_FUNCTION << ":" << __LINE__ << "] "
#define LOG_FATAL(logger) BOOST_LOG_SEV(logger.get_logger(), boost::log::trivial::fatal) << "[" << BOOST_CURRENT_FUNCTION << ":" << __LINE__ << "] "

#endif
