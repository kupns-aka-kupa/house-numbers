cmake_minimum_required(VERSION 3.15)

project(mnist-app VERSION 0.0.1 LANGUAGES CXX)

find_package(Boost COMPONENTS program_options REQUIRED)

file(GLOB SOURCE_FILES ${PROJECT_SOURCE_DIR}/*.cpp)
file(GLOB HEADER_FILES ${PROJECT_SOURCE_DIR}/*.hpp)
set(PROJECT_SOURCES
        ${SOURCE_FILES}
        ${HEADER_FILES})

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

target_compile_definitions(${PROJECT_NAME}
        PUBLIC
        PROJECT_NAME="${PROJECT_NAME}"
        PROJECT_VERSION="${PROJECT_VERSION}")

target_link_libraries(${PROJECT_NAME}
        PRIVATE
        ${TORCH_LIBRARIES}
        ${Boost_LIBRARIES})

target_include_directories(${PROJECT_NAME}
        PRIVATE
        ${TORCH_INCLUDE_DIRS}
        ${Boost_INCLUDE_DIR})
