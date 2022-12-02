cmake_minimum_required(VERSION 3.20)
project(advent_of_code_2022)
find_package(Boost)

#The Boost C++ Libraries were successfully built!
#
#The following directory should be added to compiler include paths:
#
#    /home/sean/Tarballs/boost_1_80_0
#
# The following directory should be added to linker library paths:
#
#    /home/sean/Tarballs/boost_1_80_0/stage/lib
#cmake -DBoost_NO_BOOST_CMAKE=TRUE -DBoost_NO_SYSTEM_PATHS=TRUE -DBOOST_ROOT:PATHNAME=/home/sean/Tarballs/boost_1_80_0
# 
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -Wall -Werror -Wconversion")
#set(CMAKE_CXX_FLAGS "-Wall -ftrapv")

include_directories(src/include)

add_library(aoc-2022 STATIC src/include/aoc-2022.hpp src/include/outcome.hpp src/lib/aoc-2022.cpp)

add_executable(day1 src/day1/day1.cpp)

target_link_libraries(day1 PRIVATE aoc-2022 Boost::headers)

add_executable(day2 src/day2/day2.cpp)

target_link_libraries(day2 PRIVATE aoc-2022 Boost::headers)

