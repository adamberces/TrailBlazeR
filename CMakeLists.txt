cmake_minimum_required(VERSION 3.10)
project(trailblazer)

set(EXE_NAME trailblazer)

set(CCFLAGS -O2 -std=c++17 -Wall) # -Wpedantic -Werror)
set (LINK_LIBS glfw GL dl m pthread)
###############################################################################

# Set variables for the main folder structure
set(BIN_FOLDER ${CMAKE_SOURCE_DIR}/bin)
set(SOURCE_FOLDER ${CMAKE_SOURCE_DIR}/src)
set(INCLUDE_FOLDER ${CMAKE_SOURCE_DIR}/include)

# Set basic paths for CMAKE
set(CMAKE_BINARY_DIR ${BIN_FOLDER})
set(EXECUTABLE_OUTPUT_PATH ${BIN_FOLDER})

# Define the include directory and source file list
file(GLOB EXE_SOURCE_FILES "${SOURCE_FOLDER}/*.c*")
include_directories(${INCLUDE_FOLDER})

###############################################################################

# Specify target
add_executable(${EXE_NAME} ${EXE_SOURCE_FILES})
target_compile_options(${EXE_NAME} PRIVATE ${CCFLAGS})
target_link_libraries(${EXE_NAME} ${LINK_LIBS})
