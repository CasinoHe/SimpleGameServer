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
link_directories(${CMAKE_BINARY_DIR})

if (WIN32)
	# set(CMAKE_EXE_LINKER_FLAGS /WL,/LIBPATH,./lib)
	set(CMAKE_VS_PLATFORM_NAME=x64)
	set(CMAKE_GENERATOR_PLATFORM=x64)
else()
	set(CMAKE_EXE_LINKER_FLAGS -Wl,-rpath,./lib)
endif (WIN32)

set(SRC_FILES
	${SOURCE_ROOT_DIR}/main.cpp
	${SOURCE_ROOT_DIR}/backend.cpp
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
	${SOURCE_ROOT_DIR}/object/game_object_component.cpp
	${SOURCE_ROOT_DIR}/object/object_manager.cpp
	${SOURCE_ROOT_DIR}/object/player/player_object.cpp
	${SOURCE_ROOT_DIR}/object/connection/connection_object.cpp
	${SOURCE_ROOT_DIR}/object/connection/conn_schedule_component.cpp
	# test
	${SOURCE_ROOT_DIR}/test/test.cpp
)

if (WIN32)
	link_directories(${CMAKE_BINARY_DIR}/lib)
endif(WIN32)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSION OFF)
add_executable(${PROJECT_NAME} ${SRC_FILES})
add_dependencies(${PROJECT_NAME} ${NEED_BUILD_LIBS})

if (WIN32)
	target_link_libraries(${PROJECT_NAME} PRIVATE
		${DEPENDENCIES_LIBS}
	)
else()
	target_link_libraries(${PROJECT_NAME} PRIVATE
		pthread
		${DEPENDENCIES_LIBS}
	)
endif(WIN32)

if (WIN32)
	target_compile_definitions(${PROJECT_NAME} PRIVATE -D_WIN32_WINNT=0X0A00)
else ()
	target_compile_definitions(${PROJECT_NAME} PRIVATE -DBOOST_LOG_DYN_LINK=1)
endif (WIN32)