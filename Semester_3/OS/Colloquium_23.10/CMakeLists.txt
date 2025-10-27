cmake_minimum_required (VERSION 3.15)
project(colloq)

find_package(GTest)

add_executable (colloq src/list.cpp src/main.cpp src/tasks.cpp)
target_include_directories(colloq PUBLIC headers)

if(GTest_FOUND)
	add_executable(colloq_tests tests/list_test.cpp tests/tasks_test.cpp src/list.cpp src/tasks.cpp)

	target_include_directories(colloq_tests PUBLIC headers)
	target_link_libraries(colloq_tests GTest::gtest GTest::gtest_main)

	enable_testing()
	add_test(NAME Colloq_tests COMMAND colloq_tests)
else()
	message(WARNING "GTest not found")
endif()

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET colloq PROPERTY CXX_STANDARD 20)
endif()