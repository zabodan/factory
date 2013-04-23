include_directories("inc")

file(GLOB Common_SRC "src/*")
file(GLOB Common_INC "inc/*.h")

add_library(common ${Common_SRC} ${Common_INC})
