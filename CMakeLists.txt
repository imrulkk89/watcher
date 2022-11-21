cmake_minimum_required(VERSION 3.10)
project(watcher CXX)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib)

add_executable(main 
               src/main.cpp 
               src/core/view/view.cpp
               src/core/config/config.cpp
               src/service/unix/ProcessManager.cpp
               )

# read all files in src/sample directory
file(GLOB_RECURSE SAMPLE_FILES "src/sample/*.cpp")


# create executable for each file in src/sample directory
foreach(SAMPLE_FILE ${SAMPLE_FILES})
    get_filename_component(SAMPLE_NAME ${SAMPLE_FILE} NAME_WE)
    add_executable(${SAMPLE_NAME} ${SAMPLE_FILE})
    set_target_properties(${SAMPLE_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build/bin)
endforeach()