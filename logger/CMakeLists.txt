include_directories("inc")
include_directories("${PROJECT_SOURCE_DIR}/common/inc")

file(GLOB Logger_SRC "src/*")
file(GLOB Logger_INC "inc/*.h")

add_library(logger ${Logger_SRC} ${Logger_INC})
