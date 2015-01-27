###Finds all the dependencies

#Set CMake Modules path
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/CMakeModules/")

message( STATUS "-------------------------------------------------------------------------------" )
message( STATUS "Looking for Dependencies")
message( STATUS "-------------------------------------------------------------------------------" )

#OPENCV - Git version (>=3.0 has different namespaces for variables)
FIND_PACKAGE(OpenCV 3.0.0 EXACT)
if(OpenCV_FOUND)
add_definitions( -DOPENCV_NEW=1)
include_directories(${OpenCV_INCLUDE_DIRS})
message( STATUS "OpenCV: Found (3.x)")
else()
#find minimum the 2.4.8 version
FIND_PACKAGE(OpenCV 2.4.8 REQUIRED)
if(NOT OpenCV_FOUND)
    message(FATAL_ERROR "OpenCV not found")
endif(NOT OpenCV_FOUND)
add_definitions( -DOPENCV_OLD=1)
include_directories(${OpenCV_INCLUDE_DIRS})
message( STATUS "OpenCV: Found (2.4.x)")
if(WIN32)
  if($ENV{OpenCV_BIN} MATCHES "")
    message(FATAL_ERROR "Please define OpenCV_BIN")
  endif()
endif()
endif(OpenCV_FOUND)
