
#file(GLOB CommonTests_SRC "common/*")
#file(GLOB LoggerTests_SRC "logger/*")

include_directories("${PROJECT_SOURCE_DIR}/common/inc")
include_directories("${PROJECT_SOURCE_DIR}/logger/inc")
include_directories("${PROJECT_SOURCE_DIR}/network/inc")

#link_directories("${PROJECT_BINARY_DIR}/common")
#link_directories("${PROJECT_BINARY_DIR}/logger")
#link_directories("${PROJECT_BINARY_DIR}/network")

add_executable(CommonTests
    src/ConcurQueueTest.cpp
)

target_link_libraries(CommonTests common)

add_executable(LoggerTests
    src/LoggerTest.cpp
)

target_link_libraries(LoggerTests logger common)

add_executable(NetworkTests
    src/AckUtilsTest.cpp
)

add_test(CommonTests CommonTests)
add_test(LoggerTests LoggerTests)
add_test(NetworkTests NetworkTests)
