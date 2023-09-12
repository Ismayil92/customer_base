include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.14.0
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest_main gmock_main)

add_executable(tester tester.cpp ../src/kunde.cpp)
target_link_libraries(tester
 PRIVATE
  GTest::GTest
)
target_include_directories(tester PRIVATE
../include 
../external/spdlog/include)


include(GoogleTest)
gtest_discover_tests(tester)

