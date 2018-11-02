set(SRC_FILES
	${BOOST_ROOT_DIR}/libs/atomic/src/lockpool.cpp
)

add_library(boost_atomic OBJECT ${SRC_FILES})
target_compile_options(boost_atomic PRIVATE -DBOOST_ATOMIC_STATIC_LINK=1 -DBOOST_ATOMIC_SOURCE=1)
set_property(TARGET boost_atomic PROPERTY CXX_STANDARD 11)
