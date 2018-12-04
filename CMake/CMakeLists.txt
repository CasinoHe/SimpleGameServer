# CMake for SimpleGameServer
cmake_minimum_required(VERSION 3.7.2)

project(SimpleGameServer)

# root directory
set(SOURCE_ROOT_DIR ${CMAKE_SOURCE_DIR}/..)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR})

# export compile flags
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# configure for thirdparty directories
set(PACKAGE_DIR ${SOURCE_ROOT_DIR}/ThirdpartyPackages)

if (NOT EXISTS ${PACKAGE_DIR})
	file(MAKE_DIRECTORY ${PACKAGE_DIR})
endif (NOT EXISTS ${PACKAGE_DIR})

# download all thirdparty files
include(ThirdParty)

include_directories(${SOURCE_ROOT_DIR})

set(SRC_FILES
	${SOURCE_ROOT_DIR}/main.cpp
)

set(DEPENDENCIES_LIBS 
	boost
)

set(CMAKE_CXX_STANDARD 11)
add_executable(${PROJECT_NAME} ${SRC_FILES}
)
target_link_libraries(${PROJECT_NAME}
	pthread
	${CMAKE_BINARY_DIR}/libs/boost_thread
	${CMAKE_BINARY_DIR}/libs/boost_date_time
	${CMAKE_BINARY_DIR}/libs/boost_atomic
	${CMAKE_BINARY_DIR}/libs/boost_chrono
	${CMAKE_BINARY_DIR}/libs/boost_system
	${CMAKE_BINARY_DIR}/libs/boost_filesystem
	${CMAKE_BINARY_DIR}/libs/boost_log
	${CMAKE_BINARY_DIR}/libs/boost_program_options
	${CMAKE_BINARY_DIR}/libs/boost_serialization
)
add_dependencies(${PROJECT_NAME} ${DEPENDENCIES_LIBS})

# log
target_sources(${PROJECT_NAME} PRIVATE
	${SOURCE_ROOT_DIR}/log/log.cpp
)

# options and config
target_sources(${PROJECT_NAME} PRIVATE
	${SOURCE_ROOT_DIR}/config/config.cpp
	${SOURCE_ROOT_DIR}/config/options.cpp
)

# test
target_sources(${PROJECT_NAME} PRIVATE
	${SOURCE_ROOT_DIR}/test/test.cpp
)

# gate
target_sources(${PROJECT_NAME} PRIVATE
	${SOURCE_ROOT_DIR}/network/gate_base.cpp
	${SOURCE_ROOT_DIR}/network/tcp_gate.cpp
)

# object base
target_sources(${PROJECT_NAME} PRIVATE
	${SOURCE_ROOT_DIR}/object/game_object.cpp
	${SOURCE_ROOT_DIR}/object/object_manager.cpp
)
