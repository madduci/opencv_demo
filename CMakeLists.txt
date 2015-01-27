cmake_minimum_required(VERSION 2.8.11)

#-----------------------------
# Project Settings
#-----------------------------

SET(PROJECTNAME "OpenCV Examples")
PROJECT(${PROJECTNAME} C CXX)
SET( ${PROJECT_NAME}_MAJOR_VERSION 1 )
SET( ${PROJECT_NAME}_MINOR_VERSION 0 )
SET( ${PROJECT_NAME}_PATCH_LEVEL 0 )
SET( ${PROJECT_NAME}_VERSION_STRING
        ${${PROJECT_NAME}_MAJOR_VERSION}.${${PROJECT_NAME}_MINOR_VERSION}.${${PROJECT_NAME}_PATCH_LEVEL})

#General CMake/Project Settings
INCLUDE(${CMAKE_SOURCE_DIR}/CMakeModules/project_props.cmake)
#Dependencies Settings
INCLUDE(${CMAKE_SOURCE_DIR}/CMakeModules/deps.cmake)
#Macro Definitions
INCLUDE(${CMAKE_SOURCE_DIR}/CMakeModules/macros.cmake)

#-----------------------------
# Subproject Includes
#-----------------------------
SET(PROJECT_PREFIX_NAME "cv")
ADD_SUBDIRECTORY(basic_operations)
ADD_SUBDIRECTORY(feature_extraction)
ADD_SUBDIRECTORY(image_processing)
ADD_SUBDIRECTORY(object_detection)
if(WIN32)
ADD_SUBDIRECTORY(deploy_all)	#bundle for Windows
endif(WIN32)

#-----------------------------
# Copies the test dataset into install folder
#-----------------------------
file(COPY
    ${CMAKE_SOURCE_DIR}/test_data/
    DESTINATION ${CMAKE_INSTALL_PREFIX}/bin/test_data)
