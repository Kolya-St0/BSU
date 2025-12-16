project(os_lab4)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable (Reciever src/receiver.cpp)
add_executable (Sender src/sender.cpp )