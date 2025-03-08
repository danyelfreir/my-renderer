cmake_minimum_required(VERSION 3.29)
get_filename_component(DIR_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)

# project(gfx C)
project(${DIR_NAME})

set(CMAKE_GENERATOR "Ninja")
set(CMAKE_C_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

file(GLOB C_SOURCES ${CMAKE_SOURCE_DIR}/src/*.c)

add_definitions(-DGL_SILENCE_DEPRECATION)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

add_executable(${PROJECT_NAME} ${C_SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(${DIR_NAME} OpenGL::GL)
target_link_libraries(${DIR_NAME} GLUT::GLUT)
