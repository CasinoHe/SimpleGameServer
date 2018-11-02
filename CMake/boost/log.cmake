option(BOOST_LOG_WITHOUT_DEBUG_OUTPUT "Disable debug output backend in Boost Log" ON)
option(BOOST_LOG_WITHOUT_EVENT_LOG "Disable event log backend in Boost Log" ON)
option(BOOST_LOG_WITHOUT_SYSLOG "Disable syslog backend in Boost Log" ON)

set(SRC_FILES
	${BOOST_ROOT_DIR}/libs/log/src/attribute_name.cpp
	${BOOST_ROOT_DIR}/libs/log/src/attribute_set.cpp
	${BOOST_ROOT_DIR}/libs/log/src/attribute_value_set.cpp
	${BOOST_ROOT_DIR}/libs/log/src/code_conversion.cpp
	${BOOST_ROOT_DIR}/libs/log/src/core.cpp
	${BOOST_ROOT_DIR}/libs/log/src/record_ostream.cpp
	${BOOST_ROOT_DIR}/libs/log/src/severity_level.cpp
	${BOOST_ROOT_DIR}/libs/log/src/global_logger_storage.cpp
	${BOOST_ROOT_DIR}/libs/log/src/named_scope.cpp
	${BOOST_ROOT_DIR}/libs/log/src/process_name.cpp
	${BOOST_ROOT_DIR}/libs/log/src/process_id.cpp
	${BOOST_ROOT_DIR}/libs/log/src/thread_id.cpp
	${BOOST_ROOT_DIR}/libs/log/src/timer.cpp
	${BOOST_ROOT_DIR}/libs/log/src/exceptions.cpp
	${BOOST_ROOT_DIR}/libs/log/src/default_attribute_names.cpp
	${BOOST_ROOT_DIR}/libs/log/src/default_sink.cpp
	${BOOST_ROOT_DIR}/libs/log/src/text_ostream_backend.cpp
	${BOOST_ROOT_DIR}/libs/log/src/text_file_backend.cpp
	${BOOST_ROOT_DIR}/libs/log/src/text_multifile_backend.cpp
	${BOOST_ROOT_DIR}/libs/log/src/thread_specific.cpp
	${BOOST_ROOT_DIR}/libs/log/src/once_block.cpp
	${BOOST_ROOT_DIR}/libs/log/src/timestamp.cpp
	${BOOST_ROOT_DIR}/libs/log/src/threadsafe_queue.cpp
	${BOOST_ROOT_DIR}/libs/log/src/event.cpp
	${BOOST_ROOT_DIR}/libs/log/src/trivial.cpp
	${BOOST_ROOT_DIR}/libs/log/src/spirit_encoding.cpp
	${BOOST_ROOT_DIR}/libs/log/src/format_parser.cpp
	${BOOST_ROOT_DIR}/libs/log/src/date_time_format_parser.cpp
	${BOOST_ROOT_DIR}/libs/log/src/named_scope_format_parser.cpp
	${BOOST_ROOT_DIR}/libs/log/src/unhandled_exception_count.cpp
	${BOOST_ROOT_DIR}/libs/log/src/permissions.cpp
	${BOOST_ROOT_DIR}/libs/log/src/dump.cpp
)


add_library(boost_log OBJECT ${SRC_FILES})
target_compile_options(boost_log PRIVATE -D__STDC_CONSTANT_MACROS -DBOOST_SPIRIT_USE_PHOENIX_V3=1 -DBOOST_LOG_BUILDING_THE_LIB=1 -D-ftemplate_depth-1024)
set_property(TARGET boost_log PROPERTY CXX_STANDARD 11)
