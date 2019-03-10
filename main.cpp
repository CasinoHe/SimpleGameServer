// Purpose: Server entry
// Created: 2018.11.1
// By: CasinoHe

#include "log/log.h"
#include "config/options.h"
#include "config/config.h"
#include "test/test.h"
#include "network/gate_base.h"
#include "network/tcp_gate.h"
#include "ecs/entity_base.h"

#include <iostream>
#include <list>
#include <memory>

using namespace simple_server;

void record_and_print(const char *msg)
{
  LOG_INFO(g_logger) << msg;
  std::cout << msg << std::endl;
}

void record_and_print(const std::string &msg)
{
  LOG_INFO(g_logger) << msg;
  std::cout << msg << std::endl;
}

void configure_one_gate(CConfigManager &configs, std::string &root_key, unsigned int index, std::list<std::shared_ptr<CGateBase>> &gate_list)
{
  std::string server_key = root_key + ".server" + std::to_string(index);
  std::string listen_ip_key = server_key + ".listen_ip";
  std::string listen_port_key = server_key + ".listen_port";
  std::string listen_proto_key = server_key + ".listen_proto";

  if (!configs.find_value<std::string>(listen_ip_key))
  {
    record_and_print("Simple server cannot find server" + std::to_string(index) + "'s listen_ip");
    return;
  }

  if (!configs.find_value<unsigned int>(listen_port_key))
  {
    record_and_print("Simple server cannot find server" + std::to_string(index) + "'s listen_port");
    return;
  }

  if (!configs.find_value<std::string>(listen_proto_key))
  {
    record_and_print("Simple server cannot find server" + std::to_string(index) + "'s listen_proto");
    return;
  }

  std::string listen_ip = configs.get_value<std::string>(listen_ip_key);
  unsigned int listen_port = configs.get_value<unsigned int>(listen_port_key);
  std::string listen_proto = configs.get_value<std::string>(listen_proto_key);

  if (listen_proto != "tcp" && listen_proto != "udp")
  {
    record_and_print("Simple server cannot open proto " + listen_proto + " for server" + std::to_string(index) + " now is " + listen_proto);
    return;
  }

  if (listen_proto == "tcp")
  {
    record_and_print("Simple server start " + listen_proto + " gate, ip: " + listen_ip + " port: " + std::to_string(listen_port));
    std::shared_ptr<CTcpGate> gate = std::make_shared<CTcpGate>(listen_ip, listen_port);
    gate_list.push_back(gate);
  }
  else
  {
  }
}

void configure_gates(COptionsManager &options, CConfigManager &configs, std::list<std::shared_ptr<CGateBase>> &gate_list)
{
  // config key
  std::string config_key = options.get_config_key();

  // gate list
  std::string gate_root_key = config_key + ".gate";
  std::string gate_amount_key = gate_root_key + ".amount";

  if (!configs.find_value<unsigned int>(gate_amount_key))
  {
    record_and_print("Simple server cannot find gate acmount");
    return;
  }

  unsigned int max_gate_amount = configs.get_value<unsigned int>(gate_amount_key);
  for (unsigned int index = 0; index < max_gate_amount; index++)
  {
    configure_one_gate(configs, gate_root_key, index, gate_list);
  }
}

void run()
{
  io_context.run();
}

int main(int argc, const char **argv)
{
  record_and_print("Simple server staring....");
  std::cout << std::endl;

  // parse argument
  record_and_print("Simple server is parsing argument...");
  COptionsManager options;
  if (!options.initialize_argument(argc, argv))
  {
    LOG_FATAL(g_logger) << "invalid argument";
    for (int i = 0; i < argc; i++)
    {
      LOG_FATAL(g_logger) << argv[i];
    }
    return -1;
  }
  record_and_print("Simple server finish argument parse.");
  std::cout << std::endl;

  // need help?
  if (options.need_help())
  {
    options.help();
    return 0;
  }

  // test?
  if (options.is_test())
  {
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
  if (!configs.parse_config())
  {
    record_and_print("Simple server exit because of config.More details in logs/config.log.");
    return -1;
  }
  record_and_print("Simple server read config file succeed");
  std::cout << std::endl;

  // configure gate
  std::list<std::shared_ptr<CGateBase>> gate_list;
  gate_list.clear();
  configure_gates(options, configs, gate_list);

  // poll run
  // TODO: thread
  run();

  record_and_print("Simple server exit normally");
  return 0;
}