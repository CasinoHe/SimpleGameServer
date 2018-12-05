# Download(git clone) and compile all third party repository

# thirdparty dependency
set(NEED_BUILD_LIBS
	boost
)

# boost external project build
message(STATUS "dependency ${NEED_BUILD_LIBS}")
foreach (lib ${NEED_BUILD_LIBS})
	include(${CMAKE_SOURCE_DIR}/${lib}.cmake)
endforeach ()
