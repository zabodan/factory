

file(GLOB CommonTests_SRC "common/*")
file(GLOB LoggerTests_SRC "logger/*")

include_directories("../common/inc")
include_directories("../logger/inc")

add_executable(CommonTests ${CommonTests_SRC})
add_executable(LoggerTests ${LoggerTests_SRC})

add_test(CommonTests CommonTests)
add_test(LoggerTests LoggerTests)
