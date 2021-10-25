cmake_minimum_required(VERSION 3.14)
project(my_project)

# GoogleTest requires at least C++11
set(CMAKE_CXX_STANDARD 11)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/16f637fbf4ffc3f7a01fa4eceb7906634565242f.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
  file
  file.cpp
)
target_link_libraries(
  file
  gtest_main
)

include(GoogleTest)
gtest_discover_tests(file)
