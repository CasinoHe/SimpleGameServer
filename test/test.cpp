// Purpose: main entry for test
// Create: 2018.11.7
// By: CasinoHe

#include "test/test.h"
#include "log/log.h"
#include "ecs/ecs.h"

#include <memory>

// TODO
// list all test code entry to a container

void test() {
	using namespace simple_server;

	CLogManager test_logger("test");
	LOG_TRACE(test_logger) << "Hello, World!" << "This is a trace!";
	LOG_ERROR(g_logger) << "hello, error";
}

void test_ecs() {
  // create a world
  std::shared_ptr<simple_server::ecs::CWorldBase> world = std::make_shared<simple_server::ecs::CWorldBase>();
  world->create_entity<simple_server::ecs::CEntityBase>(std::string(""));
}

namespace simple_server {
	int test_main(COptionsManager &options) {
		if (!options.is_test()) {
			return -1;
		}

		test();
    test_ecs();

		return 0;
	}
}
