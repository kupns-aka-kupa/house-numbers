cmake_minimum_required(VERSION 3.15)

project(house-numbers LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

option(POPULATE_DATASET "Ensure download MNIST dataset" OFF)

include(FetchContent)
include(ExternalProject)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules)

set(DATASET_URL http://ufldl.stanford.edu/housenumbers)
set(MNIST_URL http://yann.lecun.com/exdb/mnist)
set(PYTORCH_URL https://download.pytorch.org/libtorch/nightly/cpu/libtorch-shared-with-deps-latest.zip)
FetchContent_Declare(PyTorch URL ${PYTORCH_URL})

FetchContent_Declare(TrainData URL ${DATASET_URL}/train.tar.gz)
FetchContent_Declare(TestData URL ${DATASET_URL}/test.tar.gz)
FetchContent_Declare(ExtraData URL ${DATASET_URL}/extra.tar.gz)

FetchContent_Declare(MNIST_TrainImages
        URL ${MNIST_URL}/train-images-idx3-ubyte.gz
        DOWNLOAD_NO_EXTRACT TRUE
        DOWNLOAD_DIR ${CMAKE_CURRENT_BINARY_DIR})
FetchContent_Declare(MNIST_TestImages
        URL ${MNIST_URL}/t10k-images-idx3-ubyte.gz
        DOWNLOAD_NO_EXTRACT TRUE
        DOWNLOAD_DIR ${CMAKE_CURRENT_BINARY_DIR})

FetchContent_Declare(MNIST_TrainLabels
        URL ${MNIST_URL}/train-labels-idx1-ubyte.gz
        DOWNLOAD_NO_EXTRACT TRUE
        DOWNLOAD_DIR ${CMAKE_CURRENT_BINARY_DIR})
FetchContent_Declare(MNIST_TestLabels
        URL ${MNIST_URL}/t10k-labels-idx1-ubyte.gz
        DOWNLOAD_NO_EXTRACT TRUE
        DOWNLOAD_DIR ${CMAKE_CURRENT_BINARY_DIR})

FetchContent_MakeAvailable(PyTorch)

if (POPULATE_DATASET)
    FetchContent_MakeAvailable(
#            TrainData
#            TestData
#            ExtraData
            MNIST_TrainImages
            MNIST_TrainLabels
            MNIST_TestImages
            MNIST_TestLabels
    )
endif ()

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
        DATASET_PATH="${CMAKE_CURRENT_BINARY_DIR}"
        PROJECT_NAME="${PROJECT_NAME}"
        PROJECT_VERSION="${PROJECT_VERSION}")

target_link_libraries(${PROJECT_NAME}
        PRIVATE
        ${TORCH_LIBRARIES})

target_include_directories(${PROJECT_NAME}
        PRIVATE
        ${TORCH_INCLUDES})
