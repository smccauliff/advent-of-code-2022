cmake_minimum_required(VERSION 3.20)
project(advent_of_code_2022)
find_package(Boost REQUIRED)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

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
add_library(aoc-2022 STATIC src/include/aoc-2022.hpp src/lib/aoc-2022.cpp)

add_executable(day1 src/day1/day1.cpp)
target_link_libraries(day1 PRIVATE aoc-2022 Boost::headers)

add_executable(day2 src/day2/day2.cpp)
target_link_libraries(day2 PRIVATE aoc-2022 Boost::headers)

add_executable(day3 src/day3/day3.cpp)
target_link_libraries(day3 PRIVATE aoc-2022 Boost::headers)

add_executable(day4 src/day4/day4.cpp)
target_link_libraries(day4 PRIVATE aoc-2022 Boost::headers)

add_executable(day5 src/day5/day5.cpp)
target_link_libraries(day5 PRIVATE aoc-2022 Boost::headers)

add_executable(day6 src/day6/day6.cpp)
target_link_libraries(day6 PRIVATE aoc-2022 Boost::headers)

add_executable(day7 src/day7/day7.cpp)
target_link_libraries(day7 PRIVATE aoc-2022 Boost::headers)

add_library(forest-lib STATIC src/day8/forest-lib.hpp src/day8/forest-lib.cpp)
target_link_libraries(forest-lib PUBLIC Boost::headers)

add_executable(day8 src/day8/forest-lib.hpp src/day8/day8.cpp)
target_link_libraries(day8 PRIVATE aoc-2022 Boost::headers forest-lib)

add_executable(day9 src/day9/day9.cpp)
target_link_libraries(day9 PRIVATE aoc-2022 Boost::headers)

add_executable(day10 src/day10/day10.cpp)
target_link_libraries(day10 PRIVATE aoc-2022 Boost::headers)

enable_testing()

#Actually I'm just testing that I can get gtest to work
add_executable(day4-unit-tests src/day4/day4-unit-tests.cpp)
target_link_libraries(
  day4-unit-tests
  GTest::gtest_main
)

add_executable(day8-unit-tests src/day8/day8-unit-tests.cpp)
target_link_libraries(
  day8-unit-tests
  forest-lib
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(day4-unit-tests)
