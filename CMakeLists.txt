cmake_minimum_required(VERSION 3.0.0)


project(Mockmon VERSION 0.1.0)

#can i sp;ot this into different lines?
add_compile_options(-Wall -Wextra -Wpedantic -Wconversion -Wno-unknown-pragmas -Wchar-subscripts -Wmisleading-indentation)


add_executable(${PROJECT_NAME} mockmon-main.cpp)

#find_package(Boost COMPONENTS date_time REQUIRED)

#find_package(fmt REQUIRED)

target_include_directories(${PROJECT_NAME} PUBLIC mockmon/include)

add_subdirectory(mockmon)

target_link_libraries(${PROJECT_NAME} PRIVATE mockmon)
#target_link_libraries(${PROJECT_NAME} PRIVATE fmt::fmt-header-only)
target_compile_features(mockmon PUBLIC cxx_std_17)

#testing
enable_testing()
add_subdirectory(mockmon_testing)


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
