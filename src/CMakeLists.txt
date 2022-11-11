#Version de CMake
cmake_minimum_required(VERSION 3.7.2)

#Définition du répertoire où l'on va stocker les exécutables, les libs et les archives
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/build/)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/lib)

add_library(cclient fclient.c)
target_include_directories(cclient PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_library(cserver fserver.c)
target_include_directories(cserver PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_library(thrterm fthrterm.c)
target_include_directories(thrterm PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_library(var var.c)
target_include_directories(var PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_executable(cchat cchat.c)
target_include_directories(cchat PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(cchat PRIVATE cclient)
target_link_libraries(cchat PRIVATE cserver)
target_link_libraries(cchat PRIVATE thrterm)
target_link_libraries(cchat PRIVATE var)
