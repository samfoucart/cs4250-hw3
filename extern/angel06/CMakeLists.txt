cmake_minimum_required(VERSION 3.2)

project(Angel)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(GLEW REQUIRED)

set(SOURCES Common/InitShader.cpp)

set(HEADERS include/Angel.h
            include/CheckError.h
            include/mat.h
            include/vec.h)

add_library(Angel ${SOURCES} ${HEADERS})
target_link_libraries(Angel ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} ${GLEW_LIBRARIES})
