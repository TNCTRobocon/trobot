add_executable(parts_test
  pins_test.cpp
)

target_link_libraries(parts_test trobot gtest_main)
gtest_discover_tests(parts_test)