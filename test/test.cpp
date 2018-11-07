// Purpose: main entry for test
// Create: 2018.11.7
// By: CasinoHe

#include "test/test.h"
#include "log/log.h"

// TODO
// list all test code entry to a container

void test() {
	using namespace simple_server;

	CLogManager test_logger("test");
	LOG_TRACE(test_logger) << "Hello, World!" << "This is a trace!";
	LOG_ERROR(g_logger) << "hello, error";
}

namespace simple_server {
	int test_main(COptionsManager &options) {
		if (!options.is_test()) {
			return -1;
		}

		test();

		return 0;
	}
}
