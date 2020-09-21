cmake_minimum_required(VERSION 3.2)

project(hw0)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(GLEW REQUIRED)

set(CMAKE_CXX_STANDARD 17)

set(SOURCES src/main.cpp
            )

set(HEADERS 
            )            

add_executable(hw0 ${SOURCES} ${HEADERS})
target_link_libraries(hw0 ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} ${GLEW_LIBRARIES})