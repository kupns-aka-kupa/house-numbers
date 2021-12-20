project(mnist-tests)

find_package(Boost COMPONENTS unit_test_framework REQUIRED)

file(GLOB TESTS_SOURCES ${PROJECT_SOURCE_DIR}/*.cpp)
add_executable(${PROJECT_NAME} ${TESTS_SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${Boost_LIBRARIES})

enable_testing()
add_test(${PROJECT_NAME} ${PROJECT_NAME})