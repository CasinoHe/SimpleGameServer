set(SRC_FILES
	${BOOST_ROOT_DIR}/libs/chrono/src/chrono.cpp
	${BOOST_ROOT_DIR}/libs/chrono/src/process_cpu_clocks.cpp
	${BOOST_ROOT_DIR}/libs/chrono/src/thread_clock.cpp
)

add_library(boost_chrono OBJECT ${SRC_FILES})
target_compile_options(boost_chrono PRIVATE -DBOOST_CHRONO_STATIC_LINK=1 -DBOOST_SYSTEM_NO_DEPRECATED=1)
set_property(TARGET boost_chrono PROPERTY CXX_STANDARD 11)
