cmake_minimum_required(VERSION 3.10)

# set the project name
project(sogolo)

# include directory
include_directories(include/)

# Add source files
file(GLOB_RECURSE SOURCE_FILES
	${CMAKE_SOURCE_DIR}/src/*.cpp)
	
# Add header files
file(GLOB_RECURSE HEADER_FILES
	${CMAKE_SOURCE_DIR}/src/*.hpp)

# add the executable
add_executable(${PROJECT_NAME} ${HEADER_FILES} ${SOURCE_FILES})