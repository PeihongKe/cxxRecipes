set(threading_SRCS threading.cpp)
file(GLOB_RECURSE threading_HEADERS "*hpp")
add_library(threading ${threading_SRCS} ${threading_HEADERS})

set(Boost_USE_STATIC_LIBS ON)
link_directories(${Boost_LIBRARY_DIRS})
add_executable(test_threading  test_threading.cpp)

target_link_libraries(test_threading threading {Boost_UNIT_TEST_FRAMEWORK_LIBRARY_DEBUG} )
add_test(NAME test_threading COMMAND test_threading)