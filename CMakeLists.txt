cmake_minimum_required(VERSION 2.8)
project(rboost)


set(BOOST_ROOT "W:/devel/_libs/boost_1_53_0")
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
find_package(Boost REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})


enable_testing()

add_subdirectory(common)
add_subdirectory(logger)
add_subdirectory(tests)
