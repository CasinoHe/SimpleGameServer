cmake_minimum_required(VERSION 3.10)

include(ExternalProject)

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

ExternalProject_Add(boost
	PREFIX ${BOOST_ROOT_DIR}
	URL ${BOOST_DOWNLOAD_URL}
	URL_HASH SHA256=${BOOST_SHA256}
	UPDATE_COMMAND ""
	CONFIGURE_COMMAND ${BOOTSTRAP_COMMAND} --prefix=${CMAKE_BINARY_DIR}/boost --exec-prefix=${CMAKE_BINARY_DIR}/libs --with-libraries=thread,system,filesystem,date_time,atomic,chrono,log,program_options,serialization
	BUILD_COMMAND ${BOOST_BUILD_COMMAND} --prefix=${CMAKE_BINARY_DIR}/boost --exec-prefix=${CMAKE_BINARY_DIR}/libs --build_type=complete --build_dir=${BOOST_ROOT_DIR}/build --layout=sytem -d+2
	BUILD_IN_SOURCE FALSE
	INSTALL_COMMAND ""
)
