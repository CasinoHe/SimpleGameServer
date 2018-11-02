if (WIN32)
	set(SRC_FILES
		${BOOST_ROOT_DIR}/libs/thread/src/win32/thread.cpp
		${BOOST_ROOT_DIR}/libs/thread/src/win32/tss_pe.cpp
		${BOOST_ROOT_DIR}/libs/thread/src/future.cpp
		)
else ()
	set(SRC_FILES
		${BOOST_ROOT_DIR}/libs/thread/src/pthread/thread.cpp
		# ${BOOST_ROOT_DIR}/libs/thread/src/pthread/once.cpp
		${BOOST_ROOT_DIR}/libs/thread/src/pthread/once_atomic.cpp
		${BOOST_ROOT_DIR}/libs/thread/src/future.cpp
		)
endif ()

add_library(boost_thread OBJECT ${SRC_FILES})
target_compile_options(boost_thread PRIVATE -DBOOST_THREAD_STATIC_LINK=1 -DBOOST_THREAD_POSIX -DBOOST_THREAD_BUILD_LIB=1)
target_compile_definitions(boost_thread PRIVATE BOOST_THREAD_POSIX)
set_property(TARGET boost_thread PROPERTY CXX_STANDARD 11)
