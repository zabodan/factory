cmake_minimum_required(VERSION 2.8)
project(factory)

add_definitions("-std=c++11")

#set(BOOST_ROOT "W:/devel/_libs/boost_1_53_0")
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
#set(Boost_USE_STATIC_RUNTIME OFF)

find_package(Boost 1.53 COMPONENTS
	atomic
	exception
	chrono
	filesystem
	iostreams
	system
	thread
	timer
	test_exec_monitor
	unit_test_framework
REQUIRED)

#	"/usr/include/c++/4.7"
#	"/usr/include/c++/4.7/x86_64-linux-gnu"

include_directories(
	${Boost_INCLUDE_DIRS})

link_directories(${Boost_LIBRARY_DIRS})


enable_testing()

add_subdirectory(common)
add_subdirectory(logger)
add_subdirectory(network)
add_subdirectory(tests)
