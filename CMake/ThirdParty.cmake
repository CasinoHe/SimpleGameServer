# Download(git clone) and compile all third party repository
include(Download)

# ---------------- configure for boost --------------------
# configure for boost
set(BOOST_MAJOR_VERSION 1)
set(BOOST_MINOR_VERSION 68)
set(BOOST_PATCH_VERSION 0)
set(BOOST_SHA256 "da3411ea45622579d419bfda66f45cd0f8c32a181d84adfa936f5688388995cf")
set(BOOST_VERSION "boost_${BOOST_MAJOR_VERSION}_${BOOST_MINOR_VERSION}_${BOOST_PATCH_VERSION}")
set(BOOST_DOWNLOAD_URL "https://dl.bintray.com/boostorg/release/${BOOST_MAJOR_VERSION}.${BOOST_MINOR_VERSION}.${BOOST_PATCH_VERSION}/source/${BOOST_VERSION}.tar.gz")
set(BOOST_TAR_FILENAME ${PACKAGE_DIR}/${BOOST_VERSION}.tar.gz)
set(BOOST_ROOT_DIR ${PACKAGE_DIR}/${BOOST_VERSION})

# download and unzip boost
download_and_unzip_package(boost ${BOOST_DOWNLOAD_URL} ${BOOST_TAR_FILENAME} ${BOOST_ROOT_DIR} ${BOOST_SHA256})

# configure boost and build need libraries
set(NEED_BOOST_LIBS
	thread
	system
	filesystem
	date_time
	atomic
	chrono
	log
	program_options
)
include_directories(${BOOST_ROOT_DIR})
foreach (lib ${NEED_BOOST_LIBS})
	include(${CMAKE_SOURCE_DIR}/boost/${lib}.cmake)
endforeach ()
# ---------------- build boost end ----------------------
