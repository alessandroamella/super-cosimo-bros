cmake_minimum_required(VERSION 3.10)

project(GaetanoBros VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)

configure_file(${CMAKE_SOURCE_DIR}/src/asciiart/texts/splash.txt ${CMAKE_BINARY_DIR}/splash.txt COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/src/asciiart/texts/game_over.txt ${CMAKE_BINARY_DIR}/game_over.txt COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/src/asciiart/texts/shop.txt ${CMAKE_BINARY_DIR}/shop.txt COPYONLY)

# linka ogni file cpp
file(GLOB_RECURSE SRC_FILES src/*.cpp)

# serve ncurses
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

# aggiungi il main (l'eseguibile principale)
add_executable(${PROJECT_NAME} src/main.cpp ${SRC_FILES})

# linka ncurses
target_link_libraries(${PROJECT_NAME} ${CURSES_LIBRARIES})