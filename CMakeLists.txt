cmake_minimum_required(VERSION 3.8)
project(BaseDifGrow)

include_directories("${PROJECT_SOURCE_DIR}")

add_subdirectory(src "${PROJECT_SOURCE_DIR}/src")

add_executable(ZebraFish "${PROJECT_SOURCE_DIR}/main.cpp")

target_link_libraries(ZebraFish src)

