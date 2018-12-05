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
set(NEED_INCLUDE_DIR)

if (NOT EXISTS ${PACKAGE_DIR})
	file(MAKE_DIRECTORY ${PACKAGE_DIR})
endif (NOT EXISTS ${PACKAGE_DIR})

# download and build all thirdparty files
set(DEPENDENCIES_LIBS)
set(NEED_BUILD_LIBS)
include(ThirdParty)

include_directories(${SOURCE_ROOT_DIR})
include_directories(${NEED_INCLUDE_DIR})
link_directories(${CMAKE_BINARY_DIR}/lib)

# set(CMAKE_EXE_LINKER_FLAGS -Wl,-rpath,lib)

set(SRC_FILES
	${SOURCE_ROOT_DIR}/main.cpp
	# log
	${SOURCE_ROOT_DIR}/log/log.cpp
	# config
	${SOURCE_ROOT_DIR}/config/config.cpp
	${SOURCE_ROOT_DIR}/config/options.cpp
	# network
	${SOURCE_ROOT_DIR}/network/gate_base.cpp
	${SOURCE_ROOT_DIR}/network/tcp_gate.cpp
	# object
	${SOURCE_ROOT_DIR}/object/game_object.cpp
	${SOURCE_ROOT_DIR}/object/object_manager.cpp
	# test
	${SOURCE_ROOT_DIR}/test/test.cpp
)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSION OFF)
add_executable(${PROJECT_NAME} ${SRC_FILES})
add_dependencies(${PROJECT_NAME} ${NEED_BUILD_LIBS})

target_link_libraries(${PROJECT_NAME} PRIVATE
	pthread
	${DEPENDENCIES_LIBS}
)
target_compile_definitions(${PROJECT_NAME} PRIVATE -DBOOST_LOG_DYN_LINK=1)
