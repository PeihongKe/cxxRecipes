set(performance_SRCS 
typeConversion.cpp)


file(GLOB_RECURSE performance_HEADERS "*hpp")
add_library(performance ${performance_SRCS} ${performance_HEADERS})

set(Boost_USE_STATIC_LIBS ON)
link_directories(${Boost_LIBRARY_DIRS})
