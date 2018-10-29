set(SRC_FILES
	${BOOST_ROOT_DIR}/libs/date_time/src/gregorian/greg_month.cpp
	${BOOST_ROOT_DIR}/libs/date_time/src/gregorian/greg_weekday.cpp
	${BOOST_ROOT_DIR}/libs/date_time/src/gregorian/date_generators.cpp
)

add_library(boost_date_time OBJECT ${SRC_FILES})
target_compile_options(boost_date_time PRIVATE -DBOOST_DATE_TIME_STATIC_LINK=1 -DDATE_TIME_INLINE=1)
set_property(TARGET boost_date_time PROPERTY CXX_STANDARD 11)
