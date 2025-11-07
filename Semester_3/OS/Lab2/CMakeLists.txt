cmake_minimum_required(VERSION 3.8)
project(os_lab2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

find_package(GTest)

include_directories(include)

add_executable (win_api_threads src/main_win_api.cpp)
add_executable (std_threads src/main_std_thread.cpp src/std_thread.cpp)

if(GTest_FOUND)
	add_executable(std_threads_test tests/std_thread_test.cpp src/std_thread.cpp)

	target_include_directories(std_threads_test PUBLIC include)
	target_link_libraries(std_threads_test GTest::gtest GTest::gtest_main)

	enable_testing()
	add_test(NAME std_threads_test COMMAND std_threads_test)
else()
	message(WARNING "GTest not found")
endif()