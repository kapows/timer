cmake_minimum_required(VERSION 3.8)

project ("timer" 
    LANGUAGES CXX
    VERSION 0.0.0)

add_library(timer INTERFACE)
add_library(timer::timer ALIAS timer)
target_compile_features(timer INTERFACE cxx_std_17)
target_include_directories(timer INTERFACE include)

if(BUILD_TESTING)
    enable_testing()
    add_subdirectory("include/timer")
endif()
