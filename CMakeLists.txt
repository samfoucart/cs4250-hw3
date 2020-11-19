cmake_minimum_required(VERSION 3.2)

project(hw2)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(GLEW REQUIRED)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(extern/angel06)

set(SOURCES src/main.cpp
            src/SpaceProgram.cpp
            src/ProgramGraph.cpp)

set(HEADERS include/SpaceProgram.hpp
            include/ProgramGraph.hpp
            include/Drawable.hpp
            include/Drawables/Cube.h include/Drawables/Cone.h include/Drawables/Sphere.h src/Drawables/Cone.cpp src/Drawables/Sphere.cpp)

add_executable(hw2 ${SOURCES} ${HEADERS})
target_link_libraries(hw2 Angel ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} ${GLEW_LIBRARIES})
target_include_directories(hw2 PUBLIC include ${ANGEL_INCLUDE_DIRS} ${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS})