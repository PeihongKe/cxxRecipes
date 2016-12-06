set(bitMan_SRCS bitManipulation.cpp)
file(GLOB_RECURSE bitMan_HEADERS "*hpp")
add_library(bitMan ${bitMan_SRCS} ${bitMan_HEADERS})

set(Boost_USE_STATIC_LIBS ON)
link_directories(${Boost_LIBRARY_DIRS})
add_executable(test_bitMan  test_bitManipulation.cpp)

target_link_libraries(test_bitMan bitMan ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY} )
add_test(NAME test_bitMan COMMAND test_bitMan)