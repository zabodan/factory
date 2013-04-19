
#file(GLOB CommonTests_SRC "common/*")
#file(GLOB LoggerTests_SRC "logger/*")

include_directories("../common/inc")
include_directories("../logger/inc")
include_directories("../network/inc")


add_executable(CommonTests
    src/ConcurQueueTest.cpp)

add_executable(LoggerTests
    src/StreamLoggerTest.cpp)

add_executable(NetworkTests
    src/AckUtilsTest.cpp)

add_test(CommonTests CommonTests)
add_test(LoggerTests LoggerTests)
add_test(NetworkTests NetworkTests)
