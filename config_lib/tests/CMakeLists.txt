add_executable(test_configlib
    test_main.cpp
)

# Link library
target_link_libraries(test_configlib PRIVATE configlib)

# Register test
add_test(NAME ConfigTests COMMAND test_configlib)
