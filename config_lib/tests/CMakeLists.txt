add_executable(test_configlib
    test_main.cpp
)

# Link library
target_link_libraries(test_configlib PRIVATE configlib)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/test_config 
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# Register test
add_test(NAME ConfigTests COMMAND test_configlib)
