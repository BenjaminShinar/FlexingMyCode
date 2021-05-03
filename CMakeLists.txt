cmake_minimum_required(VERSION 3.0.0)


project(Mockmon VERSION 0.1.0)
#find_package(fmt REQUIRED)


include(CTest)
enable_testing()
add_compile_options(-Wall -Wextra -Wpedantic)
add_executable(${PROJECT_NAME} mockmon-main.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC mockmon/include)


add_subdirectory(mockmon)
target_link_libraries(${PROJECT_NAME} PRIVATE mockmon)
target_compile_features(mockmon PUBLIC cxx_std_17)

#target_link_libraries(${PROJECT_NAME} fmt fmt)


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
