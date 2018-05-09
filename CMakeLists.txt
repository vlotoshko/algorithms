cmake_minimum_required(VERSION 2.8.12)

project(algorithms)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(LINKER_FLAGS "-pthread")
set(CMAKE_EXE_LINKER_FLAGS ${LINKER_FLAGS})

include_directories(Search)
include_directories(Sort)
include_directories(Structures)

set(CPP_FILES
    "tools.cpp"
    "main.cpp"
    )

set(HPP_FILES
    "ITestable.hpp"
    )

set(FILES ${CPP_FILES} ${HPP_FILES})

add_executable(${PROJECT_NAME} ${FILES})
