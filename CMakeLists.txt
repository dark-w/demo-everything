cmake_minimum_required(VERSION 3.16)

project(push-the-box)

aux_source_directory(lib LIB_LIST)
aux_source_directory(src SRC_LIST)
aux_source_directory(sokoban SOKOBAN_LIST)

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/include/sokoban)

add_executable(push-the-box ${LIB_LIST} ${SRC_LIST} ${SOKOBAN_LIST})




