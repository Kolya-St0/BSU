add_executable (os_lab1 "Main.cpp" "employee.h")

add_executable(Creator Creator.cpp)
add_executable(Reporter Reporter.cpp)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET os_lab1 PROPERTY CXX_STANDARD 20)
endif()