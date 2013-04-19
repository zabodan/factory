
#file(GLOB CommonTests_SRC "common/*")
#file(GLOB LoggerTests_SRC "logger/*")

include_directories("../common/inc")
include_directories("../logger/inc")

add_executable(CommonTests
    src/ConcurQueueTest.cpp)

add_executable(LoggerTests
    src/StreamLoggerTest.cpp)

add_test(CommonTests CommonTests)
add_test(LoggerTests LoggerTests)
