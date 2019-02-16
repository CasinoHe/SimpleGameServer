cmake_minimum_required(VERSION 3.7.2)

include(ExternalProject)

if (APPLE)
	set(DYNAMIC_LIRBRARY_SUFFIX dylib)
elseif (UNIX)
	set(DYNAMIC_LIRBRARY_SUFFIX so)
elseif (WIN32)
	set(DYNAMIC_LIRBRARY_SUFFIX lib)
endif ()

set(BOOST_MAJOR_VERSION 1)
set(BOOST_MINOR_VERSION 68)
set(BOOST_PATCH_VERSION 0)
set(BOOST_SHA256 "da3411ea45622579d419bfda66f45cd0f8c32a181d84adfa936f5688388995cf")
set(BOOST_VERSION "boost_${BOOST_MAJOR_VERSION}_${BOOST_MINOR_VERSION}_${BOOST_PATCH_VERSION}")
set(BOOST_DOWNLOAD_URL "https://dl.bintray.com/boostorg/release/${BOOST_MAJOR_VERSION}.${BOOST_MINOR_VERSION}.${BOOST_PATCH_VERSION}/source/${BOOST_VERSION}.tar.gz")
set(BOOST_TAR_FILENAME ${PACKAGE_DIR}/${BOOST_VERSION}.tar.gz)
set(BOOST_ROOT_DIR ${PACKAGE_DIR}/${BOOST_VERSION})

if (CMAKE_SIZEOF_VOID_P EQUAL 8)
	set(BOOST_ADDRESS_MODEL 64)
else ()
	set(BOOST_ADDRESS_MODEL 32)
endif ()

if (WIN32)
	set(BOOTSTRAP_COMMAND bootstrap.bat)
	set(BOOST_BUILD_COMMAND b2.exe)
else ()
	set(BOOTSTRAP_COMMAND ./bootstrap.sh)
	set(BOOST_BUILD_COMMAND ./b2)
endif ()

# boost libs
set(NEED_BOOST_LIBS
	thread
	date_time
	atomic
	chrono
	system
	filesystem
	program_options
	serialization
	log
	regex
)

set(BOOST_BUILD_LIBRARIES)
foreach(lib ${NEED_BOOST_LIBS})
	string(APPEND BOOST_BUILD_LIBRARIES ${lib},)
endforeach()

ExternalProject_Add(boost
	PREFIX ${BOOST_ROOT_DIR}
	URL ${BOOST_DOWNLOAD_URL}
	URL_HASH SHA256=${BOOST_SHA256}
	UPDATE_COMMAND ""
	CONFIGURE_COMMAND ${BOOTSTRAP_COMMAND} --prefix=${CMAKE_BINARY_DIR} --with-libraries=${BOOST_BUILD_LIBRARIES}
	BUILD_COMMAND ${BOOST_BUILD_COMMAND} --prefix=${CMAKE_BINARY_DIR} --stagedir=${CMAKE_BINARY_DIR} --layout=system -d+2 define=BOOST_USE_WINAPI_VERSION=0x0A00 variant=release link=shared threading=multi address-model=${BOOST_ADDRESS_MODEL} stage
	BUILD_IN_SOURCE TRUE
	INSTALL_COMMAND ""
)

if (WIN32)
	foreach (lib ${NEED_BOOST_LIBS})
		list(APPEND DEPENDENCIES_LIBS boost_${lib}.${DYNAMIC_LIRBRARY_SUFFIX})
	endforeach()
else ()
	foreach (lib ${NEED_BOOST_LIBS})
		list(APPEND DEPENDENCIES_LIBS ${CMAKE_BINARY_DIR}/lib/libboost_${lib}.${DYNAMIC_LIRBRARY_SUFFIX})
	endforeach()
endif(WIN32)

list(APPEND NEED_INCLUDE_DIR ${BOOST_ROOT_DIR}/src/boost)
