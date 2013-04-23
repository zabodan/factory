include_directories("inc")

file(GLOB Network_SRC "src/*")
file(GLOB Network_INC "inc/*.h")

add_library(network ${Network_SRC} ${Network_INC})
