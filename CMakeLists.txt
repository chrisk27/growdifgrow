cmake_minimum_required(VERSION 3.8)
project(GrowDifGrow)

include_directories("${PROJECT_SOURCE_DIR}")

add_subdirectory(src "${PROJECT_SOURCE_DIR}/src")

add_executable(ZebraFish "${PROJECT_SOURCE_DIR}/main.cpp")

set(Boost_ADDITIONAL_VERSIONS "1.69" "1.69.0" "")
set(BOOST_ROOT "/home/chris/boost_1_69_0")
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.69.0 REQUIRED COMPONENTS filesystem)
message(STATUS "Boost version: ${Boost_VERSION}")

if(NOT TARGET Boost::filesystem)
    add_library(Boost::filesystem IMPORTED INTERFACE)
    set_property(TARGET Boost::filesystem PROPERTY
        INTERFACE_INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR})
    set_property(TARGET Boost::filesystem PROPERTY
        INTERFACE_LINK_LIBRARIES ${Boost_LIBRARIES})
endif()

target_link_libraries(ZebraFish PUBLIC Boost::filesystem src)
