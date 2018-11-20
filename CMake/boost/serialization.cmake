set(SRC_FILES
	${BOOST_ROOT_DIR}/libs/serialization/src/basic_archive
	${BOOST_ROOT_DIR}/libs/serialization/src/basic_iarchive
	${BOOST_ROOT_DIR}/libs/serialization/src/basic_iserializer
	${BOOST_ROOT_DIR}/libs/serialization/src/basic_oarchive
	${BOOST_ROOT_DIR}/libs/serialization/src/basic_oserializer
	${BOOST_ROOT_DIR}/libs/serialization/src/basic_pointer_iserializer
	${BOOST_ROOT_DIR}/libs/serialization/src/basic_pointer_oserializer
	${BOOST_ROOT_DIR}/libs/serialization/src/basic_serializer_map
	${BOOST_ROOT_DIR}/libs/serialization/src/basic_text_iprimitive
	${BOOST_ROOT_DIR}/libs/serialization/src/basic_text_oprimitive
	${BOOST_ROOT_DIR}/libs/serialization/src/basic_xml_archive
	${BOOST_ROOT_DIR}/libs/serialization/src/binary_iarchive
	${BOOST_ROOT_DIR}/libs/serialization/src/binary_oarchive
	${BOOST_ROOT_DIR}/libs/serialization/src/extended_type_info
	${BOOST_ROOT_DIR}/libs/serialization/src/extended_type_info_typeid
	${BOOST_ROOT_DIR}/libs/serialization/src/extended_type_info_no_rtti
	${BOOST_ROOT_DIR}/libs/serialization/src/polymorphic_iarchive
	${BOOST_ROOT_DIR}/libs/serialization/src/polymorphic_oarchive
	${BOOST_ROOT_DIR}/libs/serialization/src/stl_port
	${BOOST_ROOT_DIR}/libs/serialization/src/text_iarchive
	${BOOST_ROOT_DIR}/libs/serialization/src/text_oarchive
	${BOOST_ROOT_DIR}/libs/serialization/src/void_cast
	${BOOST_ROOT_DIR}/libs/serialization/src/archive_exception
	${BOOST_ROOT_DIR}/libs/serialization/src/xml_grammar
	${BOOST_ROOT_DIR}/libs/serialization/src/xml_iarchive
	${BOOST_ROOT_DIR}/libs/serialization/src/xml_oarchive
	${BOOST_ROOT_DIR}/libs/serialization/src/xml_archive_exception
	${BOOST_ROOT_DIR}/libs/serialization/src/codecvt_null
	${BOOST_ROOT_DIR}/libs/serialization/src/utf8_codecvt_facet
)

add_library(boost_serialization OBJECT ${SRC_FILES})
target_compile_options(boost_serialization PRIVATE -DBOOST_SERIALIZATION_STATIC_LINK=1)
set_property(TARGET boost_serialization PROPERTY CXX_STANDARD 11)

if (WIN32)
	target_sources(boost_serialization PRIVATE
		${BOOST_ROOT_DIR}/libs/serialization/src/basic_text_wiprimitive
		${BOOST_ROOT_DIR}/libs/serialization/src/basic_text_woprimitive
		${BOOST_ROOT_DIR}/libs/serialization/src/text_wiarchive
		${BOOST_ROOT_DIR}/libs/serialization/src/text_woarchive
		${BOOST_ROOT_DIR}/libs/serialization/src/xml_wgrammar
		${BOOST_ROOT_DIR}/libs/serialization/src/xml_wiarchive
		${BOOST_ROOT_DIR}/libs/serialization/src/xml_woarchive
		)
	target_compile_options(boost_serialization PRIVATE -D/Gy -D_SCL_SECURE_NO_WARNINGS)
endif ()
