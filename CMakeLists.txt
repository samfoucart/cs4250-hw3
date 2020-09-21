cmake_minimum_required(VERSION 3.2)

project(hw0)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(GLEW REQUIRED)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(extern/angel06)

set(SOURCES src/main.cpp
            src/gasket.cpp)

set(HEADERS include/gasket.h
            )            

add_executable(hw0 ${SOURCES} ${HEADERS})
target_link_libraries(hw0 Angel ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} ${GLEW_LIBRARIES})
target_include_directories(hw0 PUBLIC ${ANGEL_INCLUDE_DIRS} include)