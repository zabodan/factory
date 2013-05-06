
#file(GLOB CommonTests_SRC "common/*")
#file(GLOB LoggerTests_SRC "logger/*")

include_directories("${PROJECT_SOURCE_DIR}/common/inc")
include_directories("${PROJECT_SOURCE_DIR}/logger/inc")
include_directories("${PROJECT_SOURCE_DIR}/network/inc")

#message("BOOST = ${Boost_LIBRARIES}")

add_executable(CommonTests
    src/ConcurQueueTest.cpp)

target_link_libraries(CommonTests
    common
    ${Boost_LIBRARIES} rt)

add_executable(LoggerTests
    src/LoggerTest.cpp)

target_link_libraries(LoggerTests
    logger
    common
    ${Boost_LIBRARIES} rt)

add_executable(NetworkTests
    src/AckUtilsTest.cpp)

target_link_libraries(NetworkTests
    logger
    common
    ${Boost_LIBRARIES} rt)

add_test(CommonTests CommonTests)
add_test(LoggerTests LoggerTests)
add_test(NetworkTests NetworkTests)
