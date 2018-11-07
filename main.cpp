// Purpose: Server entry
// Created: 2018.11.1
// By: CasinoHe

#include "log/log.h"
#include "config/options.h"
#include "test/test.h"

#include <iostream>

using namespace simple_server;

void record_and_print(const char *msg) {
	LOG_INFO(g_logger) << msg;
	std::cout << msg << std::endl;
}


int main(int argc, const char **argv) {
	record_and_print("Simple server staring....");

	// parse argument
	COptionsManager options;
	if (!options.initialize_argument(argc, argv)) {
		LOG_FATAL(g_logger) << "invalid argument";
		for (int i = 0; i < argc; i++) {
			LOG_FATAL(g_logger) << argv[i];
		}
		return -1;
	}

	// test?
	if (options.is_test()) {
		test_main(options);
		record_and_print("Simple server exit normally for test finished.");
		return 0;
	}

	// get config file
	std::string config_path(options.get_config_filepath());

	record_and_print("Simple server exit normally");
	return 0;
}
