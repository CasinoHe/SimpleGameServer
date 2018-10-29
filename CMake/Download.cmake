# cmake download functions

function(download_and_unzip_package package_name package_url package_tar_name package_file_name package_sha256)
	message(STATUS "Checking ${package_name} files .....")
	set(DOWNLOAD_FILE TRUE)
	if (EXISTS ${package_tar_name})
		set(FILE_SHA256 "")
		file(SHA256 ${package_tar_name} FILE_SHA256)
		if (NOT FILE_SHA256 STREQUAL package_sha256)
			message(STATUS "SHA256 checking ${package_name} failed!")
		else ()
			set(DOWNLOAD_FILE FALSE)
			message(STATUS "Found ${package_name} download file")
		endif ()
	endif ()

	if (DOWNLOAD_FILE)
		message(STATUS "downloading file: ${package_url}")
		file(DOWNLOAD ${package_url} ${package_tar_name}
			SHOW_PROGRESS
			EXPECTED_HASH SHA256=${package_sha256})
	endif ()

	if (NOT EXISTS ${package_file_name})
		message(STATUS "unzip file: ${package_file_name}")
		file(MAKE_DIRECTORY ${package_file_name})
		execute_process(COMMAND tar -xzf ${package_tar_name} -C ${PACKAGE_DIR}
			WORKING_DIRECTORY ${SOURCE_ROOT_DIR}
			RESULT_VARIABLE TAR_RESULT
			OUTPUT_VARIABLE TAR_OUTPUT
			ERROR_VARIABLE TAR_ERROR)
		
		if (NOT ${TAR_ERROR} STREQUAL "")
			message(FATAL_ERROR "Decompress ${package_name} FAILED.Message: ${TAR_ERROR}")
		endif ()
	else ()
		message(STATUS "Decompress file exists.Skip.")
	endif ()
endfunction ()
