
#file(GLOB Tests_SRC "src/*")
#file(GLOB Tests_INC "inc/*.h")

include_directories(../logger/inc)
include_directories(../common/inc)

add_executable(LoggerTests
    src/StreamLoggerTest.cpp)

add_test(LoggerTests LoggerTests)
