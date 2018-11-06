// Purpose: Server entry
// Created: 2018.11.1
// By: CasinoHe

#include "log/log.h"

#include <iostream>

void test() {
	using namespace simple_server;

	g_logger(LOG_INFO) << "Hello, world!";
	g_logger(LOG_ERROR) << "Hello, error!";
	g_logger(LOG_TRACE) << "Hello, trace!";
	g_logger(LOG_FATAL) << "Hello, fatal!";

	g_logger << LOG_FATAL << "hello, fatal" << LOG_ERROR 
		<< "hello, error" << LOG_INFO << "hello, info";
}

int main(int argc, char **argv) {
	using namespace simple_server;

	g_logger.info("Simple server engine starting.......");

	test();

	g_logger.info("Simple server exit normally.");
	return 0;
}
