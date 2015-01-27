cmake_minimum_required(VERSION 2.8.11)

project("Deploy" C CXX)

#Suppressing CMAKE 3.0 warnings
if(POLICY CMP0043)
cmake_policy(SET CMP0043 OLD)
endif()

#-----------------------------
# Install setup
#-----------------------------
if(WIN32)
	set(INSTALL_PATH ${CMAKE_INSTALL_PREFIX}/bin)
	if(CMAKE_BUILD_TYPE MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
	  #Prepares the files to be copied
	  file(GLOB LibraryFiles $ENV{OpenCV_BIN}/opencv*.dll) 
	else()
	  #Prepares the files to be copied
	  file(GLOB LibraryFiles $ENV{OpenCV_BIN}/opencv*d.dll $ENV{OpenCV_BIN}/opencv_ffmpeg*.dll) 
	endif()
	install(FILES ${LibraryFiles} DESTINATION ${INSTALL_PATH})
	set(LIB_LOCS ${LIB_LOCS} ${INSTALL_PATH})

	configure_file(
	    "${CMAKE_SOURCE_DIR}/CMakeModules/CPackFixupBundle.cmake.in"
	    "${CMAKE_BINARY_DIR}/CPackFixupBundle.cmake"
	    @ONLY
	)

	INSTALL(SCRIPT ${CMAKE_BINARY_DIR}/CPackFixupBundle.cmake)
endif(WIN32)