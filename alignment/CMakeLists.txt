set(align_SRCS alignment.cpp)
file(GLOB_RECURSE align_HEADERS "*hpp")
add_library(align ${align_SRCS} ${align_HEADERS})

set(Boost_USE_STATIC_LIBS ON)
link_directories(${Boost_LIBRARY_DIRS})


add_executable(test_align  test_alignment.cpp)

target_link_libraries(test_align align ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY} )
add_test(NAME test_align COMMAND test_align)