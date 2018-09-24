set(performance_SRCS performance.cpp)

file(GLOB_RECURSE performance_HEADERS "*hpp")
add_library(performance ${performance_SRCS} ${performance_HEADERS})

set(Boost_USE_STATIC_LIBS ON)
link_directories(${Boost_LIBRARY_DIRS})
add_executable(test_performance test_performance.cpp)

target_link_libraries(test_performance performance {Boost_UNIT_TEST_FRAMEWORK_LIBRARY_DEBUG} )
add_test(NAME test_performance COMMAND test_performance)