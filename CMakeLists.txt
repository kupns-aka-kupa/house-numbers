cmake_minimum_required(VERSION 3.14)

project(house-numbers LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

include(FetchContent)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules)

set(DATASET_URL http://ufldl.stanford.edu/housenumbers)
set(PYTORCH_URL https://download.pytorch.org/libtorch/nightly/cpu/libtorch-shared-with-deps-latest.zip)
FetchContent_Declare(PyTorch URL ${PYTORCH_URL})

FetchContent_Declare(TrainData URL ${DATASET_URL}/train.tar.gz)
FetchContent_Declare(TestData URL ${DATASET_URL}/test.tar.gz)
FetchContent_Declare(ExtraData URL ${DATASET_URL}/extra.tar.gz)

FetchContent_MakeAvailable(
        PyTorch
        TrainData
        TestData
        ExtraData
)

set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} ${pytorch_SOURCE_DIR})

find_package(Python3 COMPONENTS Interpreter REQUIRED)

find_package(Torch REQUIRED)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${TORCH_CXX_FLAGS}")

file(GLOB SOURCE_FILES ${PROJECT_SOURCE_DIR}/*.cpp)
file(GLOB HEADER_FILES ${PROJECT_SOURCE_DIR}/*.hpp)
set(PROJECT_SOURCES
        ${SOURCE_FILES}
        ${HEADER_FILES})

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

target_compile_definitions(${PROJECT_NAME}
        PUBLIC
        PROJECT_NAME="${PROJECT_NAME}"
        DATASET_PATH="${traindata_SOURCE_DIR}"
        PROJECT_VERSION="${PROJECT_VERSION}")

target_link_libraries(${PROJECT_NAME}
        PRIVATE
        ${TORCH_LIBRARIES})

target_include_directories(${PROJECT_NAME}
        PRIVATE
        ${TORCH_INCLUDES})
