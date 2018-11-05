// Purpose: Server entry
// Created: 2018.11.1
// By: CasinoHe

#include "log/log.h"

#include <iostream>

int main(int argc, char **argv) {
	simple_server::g_logger.info("Simple server engine starting.......");
	simple_server::g_logger << "adfasdfasdf";
	return 0;
}
