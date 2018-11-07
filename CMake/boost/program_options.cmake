set(SRC_FILES
	${BOOST_ROOT_DIR}/libs/program_options/src/cmdline.cpp
	${BOOST_ROOT_DIR}/libs/program_options/src/config_file.cpp
	${BOOST_ROOT_DIR}/libs/program_options/src/convert.cpp
	${BOOST_ROOT_DIR}/libs/program_options/src/options_description.cpp
	${BOOST_ROOT_DIR}/libs/program_options/src/parsers.cpp
	${BOOST_ROOT_DIR}/libs/program_options/src/positional_options.cpp
	${BOOST_ROOT_DIR}/libs/program_options/src/split.cpp
	${BOOST_ROOT_DIR}/libs/program_options/src/utf8_codecvt_facet.cpp
	${BOOST_ROOT_DIR}/libs/program_options/src/value_semantic.cpp
	${BOOST_ROOT_DIR}/libs/program_options/src/variables_map.cpp
	${BOOST_ROOT_DIR}/libs/program_options/src/winmain.cpp
)

add_library(boost_program_options OBJECT ${SRC_FILES})
set_property(TARGET boost_program_options PROPERTY CXX_STANDARD 11)
