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

set(CMAKE_CXX_STANDARD 11)
add_executable(${PROJECT_NAME} ${SRC_FILES}
	$<TARGET_OBJECTS:boost_thread>
	$<TARGET_OBJECTS:boost_date_time>
	$<TARGET_OBJECTS:boost_atomic>
	$<TARGET_OBJECTS:boost_chrono>
	$<TARGET_OBJECTS:boost_system>
	$<TARGET_OBJECTS:boost_filesystem>
	$<TARGET_OBJECTS:boost_log>
	$<TARGET_OBJECTS:boost_program_options>
)
target_link_libraries(${PROJECT_NAME}
	pthread
)

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
