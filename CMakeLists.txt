cmake_minimum_required(VERSION 3.10)
project(watcher CXX)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib)

add_executable(main src/main.cpp src/core/config/config.cpp)
# add precompiled library for libs/spdlog to the target 
# target_link_libraries(main PRIVATE spdlog::spdlog)