cmake_minimum_required(VERSION 3.8)

find_package(Catch2 CONFIG REQUIRED)

add_library(test_main main.cpp)
target_link_libraries(test_main PUBLIC Catch2::Catch2)

function(make_test name file)
  set(exec_name ${name}_test)
	add_executable(${exec_name} ${file})
	target_link_libraries(${exec_name} PRIVATE test_main timer::timer)
	add_test(${name} ${exec_name})
endfunction()

make_test(countdown countdown.t.cpp)
make_test(countup countup.t.cpp)