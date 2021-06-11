find_package(Catch2 REQUIRED)

include(CTest)
include(Catch)
include_directories(include)

add_library(catch_main STATIC catch_main.cpp)

target_link_libraries(catch_main PUBLIC Catch2::Catch2)
target_compile_features(catch_main PUBLIC cxx_std_17)



add_executable(testingExample test_examples.cpp)
target_link_libraries(testingExample PRIVATE catch_main)

# this replacs add_test, somehow?
# automatically discover tests that are defined in catch based test files you can modify the unittests. Set TEST_PREFIX
# to whatever you want, or use different for different binaries
catch_discover_tests(
    testingExample
  TEST_PREFIX
  "unittests."
  REPORTER
  xml
  OUTPUT_DIR
  .
  OUTPUT_PREFIX
  "unittests."
  OUTPUT_SUFFIX
  .xml)

#this is the actual tests, just add the cpp files here to include them in the target?
add_executable(testingMockmon mockmon_test.cpp battle_testing.cpp)
target_link_libraries(testingMockmon PRIVATE catch_main)
target_link_libraries(testingMockmon PRIVATE mockmon)



# this replacs add_test, somehow?
# automatically discover tests that are defined in catch based test files you can modify the unittests. Set TEST_PREFIX
# to whatever you want, or use different for different binaries

# maybe there is a way to push more than one target here?
#use properties for timeout
catch_discover_tests(
    testingMockmon
    TEST_PREFIX  "unittests."
    PROPERTIES TIMEOUT 10 
    REPORTER  xml
    OUTPUT_DIR  .
    OUTPUT_PREFIX   "unittests."
    OUTPUT_SUFFIX  .xml)

