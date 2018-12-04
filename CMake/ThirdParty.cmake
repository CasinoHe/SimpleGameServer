# Download(git clone) and compile all third party repository

# boost external project build
foreach (lib ${DEPENDENCIES_LIBS})
	include(${lib}.cmake)
endforeach ()
