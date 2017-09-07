project(app)

# DEPENDENCIES

# GLFW
find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)

#GLU
pkg_search_module(GLU REQUIRED glu)

# library search path
set(ENV{PKG_CONFIG_PATH} "$ENV{PKG_CONFIG_PATH}:/usr/local/lib/pkgconfig")
set(ENV{LD_LIBRARY_PATH} "ENV{LD_LIBRARY_PATH}:/usr/local/lib")

# build dir
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
# set(CMAKE_BINARY_DIR bin)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -Wall -g")

# Include dirs
include_directories(
  src/int/
  dep/linmath
  dep/glad
  dep/klib
  ${GLFW_INCLUDE_DIRS}
  ${GLU_INCLUDE_DIRS})

set(VECTOR_FILES
  dep/glad/glad.c
  src/glfw.c
  src/scene_hexagons.c
  src/render_wire.c
  src/shader.c
  src/vbo.c)

add_library(vector ${VECTOR_FILES})
add_executable(test_01 test/test_01.c)

# add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/dep/glad ${CMAKE_CURRENT_BINARY_DIR}/glad)
target_link_libraries(
  test_01
  ${GLFW_LIBRARIES}
  ${GLU_LIBRARIES}
  vector m)

