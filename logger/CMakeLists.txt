include_directories(inc)

file(GLOB Logger_SRC "src/*.cpp")
file(GLOB Logger_INC "inc/*.h")

add_library(logger ${Logger_SRC} ${Logger_INC})
