cmake_minimum_required(VERSION 3.0.0)


include("cmake/HunterGate.cmake")
HunterGate(
    URL "https://github.com/ruslo/hunter/archive/v0.18.65.tar.gz"
    SHA1 "59cd3223f10ee630bc3596709a22f2fea4926a7c"
)

project(basel-devs-backend VERSION "0.0.1")

set (CMAKE_CXX_STANDARD 14) 

if (NOT BUILD_SHARED_LIBRARIES) 
  SET(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
endif() 

## Threads
find_package(Threads REQUIRED)

## Boost
hunter_add_package(Boost COMPONENTS system filesystem)
find_package(Boost 1.64 COMPONENTS system filesystem REQUIRED)
include_directories (AFTER ${Boost_INCLUDE_DIRS})

# Shippedwith

## express
hunter_add_package(OpenSSL)
hunter_add_package(Boost COMPONENTS regex coroutine context thread filesystem system date_time)
add_subdirectory(deps/express-cpp)
include_directories(AFTER deps/express-cpp/src)
include_directories(AFTER deps/express-cpp/Simple-Web-Server)

## mstch
add_subdirectory(deps/mstch)
include_directories(AFTER ${mstch_INCLUDE_DIR})

add_executable(basel-devs-backend src/main.cpp) 
target_include_directories(basel-devs-backend BEFORE PRIVATE ${CMAKE_CURRENT_LIST_DIR}/src)
target_link_libraries(basel-devs-backend
  mstch
  express-cpp
  ${Boost_LIBRARIES} 
  ${CMAKE_THREAD_LIBS_INIT})


  # Binaries packages
  # Bundling in a self-contained package
  set (BUNDLE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bundle)
  set (TARGETS_TO_BUNDLE basel-devs-backend)

  # Specify a runtimepath
  foreach(current_target_to_bundle IN ITEMS ${TARGETS_TO_BUNDLE})
    set_target_properties(${current_target_to_bundle} PROPERTIES 
      BUNDLE ON
      INSTALL_RPATH "$ORIGIN/")
  endforeach(current_target_to_bundle)

  install(TARGETS ${TARGETS_TO_BUNDLE}
    RUNTIME DESTINATION ${BUNDLE_OUTPUT_DIRECTORY} 
    BUNDLE DESTINATION ${BUNDLE_OUTPUT_DIRECTORY}
    COMPONENT Runtime)

  # Paths where to look for shared libraries
  # XXX: When cross compiling we end up with the libc in the bundle, which is a bit extreme.
  foreach(current_path IN ITEMS ${CMAKE_FIND_ROOT_PATH})
    list (APPEND POSSIBLE_LIBRARY_PATHS
      ${current_path}/lib
      ${current_path}/usr/lib
    )
  endforeach(current_path)
 
  # Specify how to fixup each app (meaning how to copy libs independently of sysroots)
  foreach(current_target_to_bundle IN ITEMS ${TARGETS_TO_BUNDLE})
    set (EXECUTABLE_SUFFIX "")
    if (WIN32)
        set (EXECUTABLE_SUFFIX ".exe")
    endif()
    install( CODE "
    include(BundleUtilities)
    fixup_bundle( \"${BUNDLE_OUTPUT_DIRECTORY}/${current_target_to_bundle}${EXECUTABLE_SUFFIX}\" \"\" \"${POSSIBLE_LIBRARY_PATHS}\" COMPONENT Runtime)
    ")
  endforeach(current_target_to_bundle)

  # Make it into a cpack (can be generated with cpack -G TGZ)
  set(CPACK_PACKAGE_NAME "basel-devs-backend")
  set(CPACK_PACKAGE_VENDOR "Le CBNA")
  set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Backend to compile the Basel model on the fly.")
  set(CPACK_PACKAGE_VERSION "${testtool-serial-ports_VERSION_MAJOR}.${testtool-serial-ports_VERSION_MINOR}.${testtool-serial-ports_VERSION_PATCH}")
  set(CPACK_PACKAGE_VERSION_MAJOR "${testtool-serial-ports_VERSION_MAJOR}")
  set(CPACK_PACKAGE_VERSION_MINOR "${testtool-serial-ports_VERSION_MINOR}")
  set(CPACK_PACKAGE_VERSION_PATCH "${testtool-serial-ports_VERSION_PATCH}") 
  set(CPACK_INSTALLED_DIRECTORIES ${BUNDLE_OUTPUT_DIRECTORY} .)
  include(CPack)

