// Purpose: Server entry
// Created: 2018.11.1
// By: CasinoHe

#include "log/log.h"

#include <iostream>

void test() {
	using namespace simple_server;

	LOG_TRACE(g_logger) << "Hello, World!" << "This is a trace!";

	LOG_ERROR(g_logger) << "hello, error";
}

int main(int argc, char **argv) {
	using namespace simple_server;
	LOG_INFO(g_logger) << "Simple server staring....";
	test();
	LOG_INFO(g_logger) << "Simple server exit normally";
	return 0;
}
