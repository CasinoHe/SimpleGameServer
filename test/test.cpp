// Purpose: main entry for test
// Create: 2018.11.7
// By: CasinoHe

#include "test/test.h"
#include "log/log.h"
#include "ecs/ecs.h"

#include <memory>
#include <functional>
#include <thread>
#include <chrono>

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
      // std::cout << "on create event received:" << entity_created_event.m_entity_ptr->get_entityid() << std::endl;
    }

    virtual ~CTestSystem() {}
  };

  struct CPositionComponent {
    CPositionComponent(float x, float y) { m_x = x;
      m_y = y;
    }

    float m_x;
    float m_y;
  };

  world->register_system<CTestSystem>();
  world->enable_system<CTestSystem>();
  world->subscribe<CTestSystem, simple_server::ecs::CEntityCreateEvent>(); // , simple_server::ecs::CEntityCreateEvent>();
  std::shared_ptr<simple_server::ecs::CEntityBase> entity_ptr = world->create_entity<simple_server::ecs::CEntityBase>("");
  world->unsubscribe<CTestSystem, simple_server::ecs::CEntityCreateEvent>();
  auto entity_ptr2 = world->create_entity<simple_server::ecs::CEntityBase>("");
  world->subscribe<CTestSystem, simple_server::ecs::CEntityCreateEvent>(); // , simple_server::ecs::CEntityCreateEvent>();
  auto entity_ptr3 = world->create_entity<simple_server::ecs::CEntityBase>("");

  world->destroy_entity(entity_ptr->get_entityid());
  world->destroy_entity(entity_ptr2->get_entityid());
  world->destroy_entity(entity_ptr3->get_entityid());

  std::this_thread::sleep_for(std::chrono::seconds(10));
  for (int i = 1; i < 10000; i++)
  {
    auto entity = world->create_entity<simple_server::ecs::CEntityBase>("");
    entity->new_component<CPositionComponent>(4.5, 3.6);
    // std::this_thread::sleep_for(std::chrono::milliseconds(100));
    auto component_ptr = entity->get_component<CPositionComponent>();
    // std::cout << "pos component.x " << component_ptr->m_x << "compoent.y " << component_ptr->m_y << std::endl;
    if (i % 2 == 0)
    {
      entity->remove_component<CPositionComponent>();
    }
    // world->destroy_entity(entity->get_entityid());
  }
  std::this_thread::sleep_for(std::chrono::seconds(100));
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
