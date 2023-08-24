cmake_minimum_required(VERSION 3.10)

project(SuperCosimoBros VERSION 1.0)

set (CMAKE_CXX_STANDARD 11)

# linka ogni file cpp
file(GLOB_RECURSE SRC_FILES src/*.cpp)

# serve ncurses
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

# aggiungi il main (l'eseguibile principale)
add_executable(${PROJECT_NAME} src/main.cpp ${SRC_FILES})

# linka ncurses
target_link_libraries(${PROJECT_NAME} ${CURSES_LIBRARIES})