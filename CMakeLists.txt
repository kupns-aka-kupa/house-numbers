cmake_minimum_required(VERSION 3.15)

project(mnist LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

option(POPULATE_DATASET "Ensure download MNIST dataset" OFF)

include(FetchContent)
include(ExternalProject)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules)

set(DATASET_URL http://ufldl.stanford.edu/housenumbers)
set(MNIST_URL http://yann.lecun.com/exdb/mnist)
set(PYTORCH_URL https://download.pytorch.org/libtorch/nightly/cpu/libtorch-cxx11-abi-shared-with-deps-latest.zip)

#ExternalProject_Add(pqxx GIT_REPOSITORY https://github.com/jtv/libpqxx.git GIT_TAG 7.2.0)
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

set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} ${pytorch_SOURCE_DIR}/share/cmake)

find_package(Boost COMPONENTS log REQUIRED)
find_package(Python3 COMPONENTS Interpreter REQUIRED)
find_package(Torch REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${TORCH_CXX_FLAGS}")

add_subdirectory(trainer)
add_subdirectory(app)
add_subdirectory(tests)
