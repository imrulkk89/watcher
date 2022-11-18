cmake_minimum_required(VERSION 3.10)
project(watcher CXX)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib)

# # check if lib/contour/build exists
# IF(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/lib/contour/build)
#    #message(SEND_ERROR "Contour binary not found. Attempting to build it.")
    
#     # if UNIX-like system
#     IF (UNIX)
#         # install dependencies
#         execute_process(COMMAND ./scripts/install_dependencies.sh WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib/contour)
    
#     ENDIF()

#     IF (WIN32)
#         # install dependencies with .\scripts\install-deps.ps1
#         execute_process(COMMAND powershell.exe -ExecutionPolicy Bypass -File .\scripts\install-deps.ps1 WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib/contour)
    
#     ENDIF()

#     # build contour 

#     # run cmake -S . -B build 
#     execute_process(COMMAND cmake -S . -B build WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib/contour)
#     # run cmake --build build/
#     execute_process(COMMAND cmake --build build/ WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib/contour)
# ENDIF()


add_executable(main 
               src/main.cpp 
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