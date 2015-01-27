cmake_minimum_required(VERSION 2.8.11)

set(APPLICATION_NAME "${PROJECT_PREFIX_NAME}_matching")
project(${APPLICATION_NAME} C CXX)

#Suppressing CMAKE 3.0 warnings
if(POLICY CMP0043)
cmake_policy(SET CMP0043 OLD)
endif()

#-----------------------------
# Generating Target
#-----------------------------

add_executable(${APPLICATION_NAME} main.cpp ${${APPLICATION_NAME}_SOURCES} ${${APPLICATION_NAME}_HEADERS})
set_target_properties( ${APPLICATION_NAME} PROPERTIES OUTPUT_NAME ${APPLICATION_NAME} )
set_target_properties( ${APPLICATION_NAME} PROPERTIES DEBUG_POSTFIX _d )

#-----------------------------
# Linking libraries
#-----------------------------

target_link_libraries(${APPLICATION_NAME} ${OpenCV_LIBRARIES})

#-----------------------------
# Install Phase
#-----------------------------

INSTALL(TARGETS ${APPLICATION_NAME}
  BUNDLE DESTINATION . COMPONENT Application
  RUNTIME DESTINATION bin COMPONENT Application
)
