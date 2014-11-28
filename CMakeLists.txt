cmake_minimum_required(VERSION 2.6)

project(monkeymusic)

# We use Casablanca for http
add_subdirectory(casablanca/Release)
include_directories(${CMAKE_CURRENT_LIST_DIR}/casablanca/Release/include)

# We need c++11
add_definitions(-std=c++11)

add_executable(monkeymusic main.cpp ai.cpp ai.h)

set(Casablanca_LIBRARY ${LIB}cpprest)
set(Casablanca_LIBRARIES ${Casablanca_LIBRARY})
target_link_libraries(monkeymusic ${Casablanca_LIBRARIES})
