cmake_minimum_required(VERSION 3.0.0)
project(basel-devs-backend VERSION "0.0.1")

set (CMAKE_CXX_STANDARD 14) 

## Threads
find_package(Threads REQUIRED)

## Boost
find_package(Boost 1.64 COMPONENTS system filesystem REQUIRED)
include_directories (AFTER ${Boost_INCLUDE_DIRS})

## lib-cpp-pre
find_package(lib-cpp-pre 1.4.2 REQUIRED)
include_directories (AFTER ${LIB_CPP_PRE_INCLUDE_DIRS})

## lib-cpp-slc
find_package(lib-cpp-slc CONFIG 2.0.1 REQUIRED)

## lib-express-cpp
find_package(libexpress 0.1.0)
include_directories(${libexpress_INCLUDE_DIR})

# Shippedwith
add_subdirectory(deps/mstch)
include_directories(${mstch_INCLUDE_DIR})

add_executable(basel-devs-backend src/main.cpp) 
target_include_directories(basel-devs-backend PRIVATE ${CMAKE_CURRENT_LIST_DIR}/src)
target_link_libraries(basel-devs-backend
  mstch
  ${libexpress_LIBRARIES}
  ${Boost_LIBRARIES} 
  ${CMAKE_THREAD_LIBS_INIT})
