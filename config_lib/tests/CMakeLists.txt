add_executable(test_configlib
    test_main.cpp
)

# Link library
target_link_libraries(test_configlib PRIVATE configlib gtest_main)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/test_config 
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# Register test
include(GoogleTest)
gtest_discover_tests(test_configlib)

#add_test(NAME ConfigTests COMMAND test_configlib)
