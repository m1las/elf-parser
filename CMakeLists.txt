cmake_minimum_required(VERSION 3.15)
project(elfparser CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# default to Debug build mode
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

add_compile_options(-Wall -Wextra -Wpedantic)


add_library(elfparser_lib
    src/elf_parser.cpp
)
target_include_directories(elfparser_lib PUBLIC include)

# CLI executable
add_executable(elfparser src/main.cpp)
target_link_libraries(elfparser PRIVATE elfparser_lib)

enable_testing()
add_subdirectory(tests)
