add_executable(test_sseclient
    test_main.cpp
)

# Link library
target_link_libraries(test_sseclient PRIVATE sseclient gtest_main)

# Register test
include(GoogleTest)
gtest_discover_tests(test_sseclient)

#add_test(NAME ConfigTests COMMAND test_configlib)
