project(os_lab3)

include_directories(include)
find_package(GTest)

add_executable (os_lab3 src/main.cpp src/marker.cpp)

if(GTest_FOUND)
	add_executable(marker_tests tests/marker_test.cpp src/marker.cpp)

	target_include_directories(marker_tests PUBLIC include)
	target_link_libraries(marker_tests GTest::gtest GTest::gtest_main)

	enable_testing()
	add_test(NAME Marker_tests COMMAND marker_tests)
else()
	message(WARNING "GTest not found")
endif()

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD_REQUIRED ON)