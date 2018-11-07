// Purpose: Log Handler
// Created: 2018.11.5
// By: CasinoHe

#include "log.h"

#include <stdexcept>

#include <boost/log/sinks.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/utility/setup.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/log/attributes.hpp>
#include <boost/log/core.hpp>
#include <boost/shared_ptr.hpp>

namespace simple_server {
	bool CLogManager::has_init = false;
	CLogManager g_logger = CLogManager("global");

	CLogManager::CLogManager(const std::string filename):
		m_filename(filename) {
			CLogManager(filename.c_str());
		}

	CLogManager::CLogManager(const char *filename):
		m_filename(filename) {
			m_level = boost::log::trivial::info;

			// static initialize
			initialize_log_sinks();

			// log sources
			if (m_filename.size() <= 0) {
				throw std::invalid_argument("cannot initialize log without filename");
			}

			m_logger.add_attribute("FileTag", boost::log::attributes::constant<std::string>(m_filename));
		}

	void CLogManager::initialize_log_sinks() {
		if (has_init) {
			return;
		}

		has_init = true;

		boost::shared_ptr<boost::log::core> core = boost::log::core::get();
		boost::log::add_common_attributes();

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
		boost::shared_ptr<SINK_TYPE> sink = boost::make_shared<SINK_TYPE>(backend);

		// log format
		namespace expression = boost::log::expressions;
		namespace attr = boost::log::attributes;
		sink->set_formatter(
				// log format [TimeStamp] [ProcessID] [ThreadID] [Severity] message
				expression::format("[%1%] [%2%] [%3%] [%4%] %5%")
				% expression::format_date_time<boost::posix_time::ptime>("TimeStamp", "%Y-%m-%d %H:%M:%S.%f")
				% expression::attr<attr::current_process_id::value_type>("ProcessID")
				% expression::attr<attr::current_thread_id::value_type>("ThreadID")
				% expression::attr<boost::log::trivial::severity_level>("Severity")
				% expression::message);
		core->add_sink(sink);
	}

	CLogManager &operator<<(CLogManager &logger, const char *msg) {
		boost::log::trivial::severity_level level = logger.get_level();
		BOOST_LOG_SEV(logger.get_logger(), level) << msg;
		return logger;
	}

	CLogManager &operator<<(CLogManager &logger, const boost::log::trivial::severity_level &level) {
		logger.set_level(level);
		return logger;
	}

	 CLogManager &CLogManager::operator()(const boost::log::trivial::severity_level &level) {
		set_level(level);
		return *this;
	}
}
