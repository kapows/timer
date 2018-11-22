cmake_minimum_required(VERSION 3.8)

project ("timer" 
    LANGUAGES CXX
    VERSION 0.0.0)

set(NAMESPACE timer)
set(INSTALL_INCLUDE_DIR include)
set(INSTALL_CONFIG_DIR lib/cmake/timer)
set(EXPORT_TARGET timer-targets)
set(CONFIG_NAME timer-config)

add_library(timer INTERFACE)
add_library(${NAMESPACE}::timer ALIAS timer)
target_compile_features(timer INTERFACE cxx_std_17)
target_include_directories(timer INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/timer>
	$<INSTALL_INTERFACE:include>
)

if(BUILD_TESTING)
    enable_testing()
    add_subdirectory("include/timer")
endif()

# INSTALL 
install(DIRECTORY include/ 
	DESTINATION ${INSTALL_INCLUDE_DIR}
	FILES_MATCHING 
		PATTERN "*.t.h" EXCLUDE
		PATTERN "*.h"
	)
install(TARGETS timer 
	EXPORT ${EXPORT_TARGET}   
)
install(EXPORT ${EXPORT_TARGET}
	NAMESPACE ${NAMESPACE}:: 
	FILE ${EXPORT_TARGET}.cmake 
	DESTINATION ${INSTALL_CONFIG_DIR}
)
# INSTALL CONFIG 
include(CMakePackageConfigHelpers)
# CONFIG
configure_package_config_file(
    ${CMAKE_CURRENT_LIST_DIR}/cmake/${CONFIG_NAME}.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/cmake/${CONFIG_NAME}.cmake
    INSTALL_DESTINATION ${INSTALL_CONFIG_DIR}
	)
# VERSION
write_basic_package_version_file(
	"${CMAKE_CURRENT_BINARY_DIR}/cmake/${CONFIG_NAME}-version.cmake"
	VERSION ${PROJECT_VERSION}
	COMPATIBILITY AnyNewerVersion
	)
install(
  FILES
    "${CMAKE_CURRENT_BINARY_DIR}/cmake/${CONFIG_NAME}.cmake"
	"${CMAKE_CURRENT_BINARY_DIR}/cmake/${CONFIG_NAME}-version.cmake"
  DESTINATION
    ${INSTALL_CONFIG_DIR}
)