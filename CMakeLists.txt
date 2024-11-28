cmake_minimum_required(VERSION 3.8)
cmake_policy(SET CMP0072 NEW)

project(2salles2ambiances)

# Set the folder where the executables are created
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

# Include glimac
add_subdirectory(glimac)

# Include src
add_subdirectory("src")
