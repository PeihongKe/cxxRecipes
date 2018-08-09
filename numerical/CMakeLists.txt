set(numerical_SRCS floating.cpp)
file(GLOB_RECURSE numerical_HEADERS "*hpp")
add_library(numerical ${numerical_SRCS} ${numerical_HEADERS})

set(Boost_USE_STATIC_LIBS ON)
link_directories(${Boost_LIBRARY_DIRS})
add_executable(test_numerical test_floating.cpp)

target_link_libraries(test_numerical numerical ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY} )
add_test(NAME test_numerical COMMAND test_numerical)