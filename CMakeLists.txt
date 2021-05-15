cmake_minimum_required(VERSION 3.0.0)


project(Mockmon VERSION 0.1.0)


add_compile_options(-Wall -Wextra -Wpedantic)
add_executable(${PROJECT_NAME} mockmon-main.cpp)

find_package(fmt REQUIRED)

target_include_directories(${PROJECT_NAME} PUBLIC mockmon/include)

add_subdirectory(mockmon)

target_link_libraries(${PROJECT_NAME} PRIVATE mockmon)
target_link_libraries(${PROJECT_NAME} PRIVATE fmt::fmt-header-only)
target_compile_features(mockmon PUBLIC cxx_std_17)



find_package(Catch2 REQUIRED)

include(CTest)
enable_testing()
add_executable(testingMain testing/catch_main.cpp)
#add_executable(testing testing/mockmon-test.cpp)
target_link_libraries(testingMain PRIVATE Catch2::Catch2)
#target_link_libraries(testing PRIVATE Catch2::Catch2)

#test name, test executable, aeguments...
add_test(TestingMainSucces testingMain)


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
