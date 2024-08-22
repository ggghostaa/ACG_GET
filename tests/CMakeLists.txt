#find test .cpp
file(GLOB_RECURSE TEST_SRC_FILES "*.cpp")

# add executable file
add_executable(runTests ${TEST_SRC_FILES})

target_include_directories(runTests PRIVATE 
    ${CMAKE_SOURCE_DIR}/include
)
# link GoogleTest lib
target_link_libraries(runTests 
    gtest gtest_main pthread
)

enable_testing()
add_test(NAME runTests COMMAND runTests)

