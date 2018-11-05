// Purpose: Log Handler
// Created: 2018.11.5
// By: CasinoHe

#include "log.h"

#include <stdexcept>

#include <boost/log/sinks.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/utility/setup.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/shared_ptr.hpp>

namespace simple_server {
	CLogManager g_logger = CLogManager("global");

	CLogManager::CLogManager(const std::string filename):
		m_filename(filename) {
			try {
				initialize();
			} catch (const std::invalid_argument &e) {
				std::cerr << e.what() << std::endl;
			} catch (const std::exception &e) {
				std::cerr << e.what() << std::endl;
			}
		}

	CLogManager::CLogManager(const char *filename):
		m_filename(filename) {
			try {
				initialize();
			} catch (const std::invalid_argument &e) {
				std::cerr << e.what() << std::endl;
			} catch (const std::exception &e) {
				std::cerr << e.what() << std::endl;
			}
		}

	void CLogManager::initialize() {
		boost::log::add_common_attributes();

		// check filename
		if (m_filename.size() <= 0) {
			throw std::invalid_argument("cannot initialize log without filename");
		}

		// file tag
		m_logger.add_attribute("FileTag", boost::log::attributes::constant<std::string>(m_filename));

		// multi-files sinks
		boost::shared_ptr<boost::log::sinks::text_multifile_backend> backend = 
			boost::make_shared<boost::log::sinks::text_multifile_backend>();

		// multi file composer
		backend->set_file_name_composer(boost::log::sinks::file::as_file_name_composer(
					boost::log::expressions::stream << "logs/" 
					<< boost::log::expressions::attr<std::string>("FileTag")
					<< ".log"));

		// sinks
		typedef boost::log::sinks::synchronous_sink<boost::log::sinks::text_multifile_backend> SINK_TYPE;
		boost::shared_ptr<SINK_TYPE> sink = boost::make_shared<SINK_TYPE>();

		// log format
		namespace expression = boost::log::expressions;
		namespace attr = boost::log::attributes;
		sink->set_formatter(
				// log format [TimeStamp] [ProcessID] [ThreadID] [Severity] [LineID] message
				expression::format("[%1%] [%2%] [%3%] [%4%] [%5%] %6%")
				% expression::format_date_time<boost::posix_time::ptime>("TimeStamp", "%Y-%m-%d %H:%M:%S.%f")
				% expression::attr<attr::current_process_id::value_type>("ProcessID")
				% expression::attr<attr::current_thread_id::value_type>("ThreadID")
				% expression::attr<boost::log::trivial::severity_level>("Severity")
				% expression::attr<unsigned int>("LineID")
				% expression::message);
	}

	void CLogManager::trace(const char *msg) {
		BOOST_LOG_SEV(m_logger, boost::log::trivial::trace) << msg;
	}

	void CLogManager::info(const char *msg) {
		BOOST_LOG_SEV(m_logger, boost::log::trivial::info) << msg;
	}

	void CLogManager::debug(const char *msg) {
		BOOST_LOG_SEV(m_logger, boost::log::trivial::debug) << msg;
	}

	void CLogManager::warning(const char *msg) {
		BOOST_LOG_SEV(m_logger, boost::log::trivial::warning) << msg;
	}

	void CLogManager::error(const char *msg) {
		BOOST_LOG_SEV(m_logger, boost::log::trivial::error) << msg;
	}

	void CLogManager::fatal(const char *msg) {
		BOOST_LOG_SEV(m_logger, boost::log::trivial::fatal) << msg;
	}

	CLogManager &operator<<(CLogManager &logger, const char *msg) {
		std::cout << msg << std::endl;
		return logger;
	}
}
