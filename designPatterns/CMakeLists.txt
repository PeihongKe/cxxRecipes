set(designPattern_SRCS 
builder.cpp
factory.cpp
singleton.cpp)


file(GLOB_RECURSE designPattern_HEADERS "*hpp")
add_library(designPatterns ${designPattern_SRCS} ${designPattern_HEADERS})

set(Boost_USE_STATIC_LIBS ON)
link_directories(${Boost_LIBRARY_DIRS})
