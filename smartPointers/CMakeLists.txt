set(smartPointers_SRCS smartPointers.cpp)
file(GLOB_RECURSE smartPointers_HEADERS "*hpp")
add_library(smartPointers ${smartPointers_SRCS} ${smartPointers_HEADERS})

set(Boost_USE_STATIC_LIBS ON)
link_directories(${Boost_LIBRARY_DIRS})
add_executable(test_smartPointers  test_smartPointers.cpp)

target_link_libraries(test_smartPointers smartPointers ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY} )
add_test(NAME test_smartPointers COMMAND test_smartPointers)