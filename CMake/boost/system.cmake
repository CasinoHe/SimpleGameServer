set(SRC_FILES
	${BOOST_ROOT_DIR}/libs/system/src/error_code.cpp
)

add_library(boost_system OBJECT ${SRC_FILES})
target_compile_options(boost_system PRIVATE -DBOOST_SYSTEM_STATIC_LINK=1)
set_property(TARGET boost_system PROPERTY CXX_STANDARD 11)
