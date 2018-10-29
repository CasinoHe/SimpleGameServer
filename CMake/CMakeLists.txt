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

include(ThirdParty)

set(SRC_FILES
	${SOURCE_ROOT_DIR}/main.cpp
)

add_executable(${PROJECT_NAME} ${SRC_FILES})
