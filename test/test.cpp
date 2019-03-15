// Purpose: main entry for test
// Create: 2018.11.7
// By: CasinoHe

#include "test/test.h"
#include "log/log.h"
#include "ecs/ecs.h"

#include <memory>
#include <functional>

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
  world->create_entity<simple_server::ecs::CEntityBase>("");

  class CTestSystem : public simple_server::ecs::CSystemBase
  {
  public:
    bool configure(std::shared_ptr<simple_server::ecs::CWorldBase> world_ptr) override
    {
      simple_server::ecs::CSystemBase::configure(world_ptr);
      // bind frame tick function
      // register_frame_tick_handler<CTestSystem>();

      // bind create entity event handler
      std::function<void (std::shared_ptr<simple_server::ecs::CWorldBase>, simple_server::ecs::CEventBase &)> function = std::bind(&CTestSystem::on_create_entity, this, std::placeholders::_1, std::placeholders::_2);
      register_event_handler<simple_server::ecs::CEntityCreateEvent>(function);
      return true;
    }

    void frame_tick(std::shared_ptr<simple_server::ecs::CWorldBase> world_ptr, simple_server::ecs::CTickEvent &event)
    {
    }

    void on_create_entity(std::shared_ptr<simple_server::ecs::CWorldBase> world_ptr, simple_server::ecs::CEventBase &event)
    {
      auto &entity_created_event = static_cast<simple_server::ecs::CEntityCreateEvent &>(event);
      std::cout << "on create event received:" << entity_created_event.m_entity_ptr->get_entityid() << std::endl;
    }

    virtual ~CTestSystem() {}
  };

  world->register_system<CTestSystem>();
  world->enable_system<CTestSystem>();
  world->subscribe<CTestSystem, simple_server::ecs::CEntityCreateEvent>(); // , simple_server::ecs::CEntityCreateEvent>();
  world->create_entity<simple_server::ecs::CEntityBase>("");
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
