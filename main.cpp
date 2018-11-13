// Purpose: Server entry
// Created: 2018.11.1
// By: CasinoHe

#include "log/log.h"
#include "config/options.h"
#include "config/config.h"
#include "test/test.h"

#include <iostream>

using namespace simple_server;

void record_and_print(const char *msg) {
	LOG_INFO(g_logger) << msg;
	std::cout << msg << std::endl;
}


void configure_server(COptionsManager &options, CConfigManager & configs) {
	// config key
	std::string config_key = options.get_config_key();

	// listen?
	std::string listen_ip_key = config_key + ".listen_ip";
	std::string listen_port_key = config_key + ".listen_port";
	if (!configs.find_value<std::string>(listen_ip_key)) {
		record_and_print("Simple server cannot find listen ip config");
		return;
	}

	if (!configs.find_value<std::string>(listen_port_key)) {
		record_and_print("Simple server cannot find listen port config");
		return;
	}

	std::string listen_ip, listen_port;
	listen_ip = configs.get_value<std::string>(listen_ip_key);
	listen_port = configs.get_value<std::string>(listen_port_key);
}


int main(int argc, const char **argv) {
	record_and_print("Simple server staring....");
	std::cout << std::endl;

	// parse argument
	record_and_print("Simple server is parsing argument...");
	COptionsManager options;
	if (!options.initialize_argument(argc, argv)) {
		LOG_FATAL(g_logger) << "invalid argument";
		for (int i = 0; i < argc; i++) {
			LOG_FATAL(g_logger) << argv[i];
		}
		return -1;
	}
	record_and_print("Simple server finish argument parse.");
	std::cout << std::endl;

	// need help?
	if (options.need_help()) {
		options.help();
		return 0;
	}

	// test?
	if (options.is_test()) {
		record_and_print("Simple server running in test mode");
		std::cout << std::endl;
		test_main(options);
		std::cout << std::endl;
		record_and_print("Simple server exit normally for test finished.");
		return 0;
	}


	// get config file
	record_and_print("Simple server is parsing config file");
	std::string config_path(options.get_config_filepath());
	CConfigManager configs(config_path);
	if (!configs.parse_config()) {
		record_and_print("Simple server exit because of config.More details in logs/config.log.");
		return -1;
	}
	record_and_print("Simple server read config file succeed");
	std::cout << std::endl;

	// configure server
	configure_server(options, configs);

	record_and_print("Simple server exit normally");
	return 0;
}
