set(SRC_FILES
	${BOOST_ROOT_DIR}/libs/filesystem/src/codecvt_error_category.cpp
	${BOOST_ROOT_DIR}/libs/filesystem/src/operations.cpp
	${BOOST_ROOT_DIR}/libs/filesystem/src/path.cpp
	${BOOST_ROOT_DIR}/libs/filesystem/src/path_traits.cpp
	${BOOST_ROOT_DIR}/libs/filesystem/src/portability.cpp
	${BOOST_ROOT_DIR}/libs/filesystem/src/unique_path.cpp
	${BOOST_ROOT_DIR}/libs/filesystem/src/utf8_codecvt_facet.cpp
	${BOOST_ROOT_DIR}/libs/filesystem/src/windows_file_codecvt.cpp
)

add_library(boost_filesystem OBJECT ${SRC_FILES})
target_compile_options(boost_filesystem PRIVATE -DBOOST_FILESYSTEM_STATIC_LINK=1)
set_property(TARGET boost_filesystem PROPERTY CXX_STANDARD 11)
