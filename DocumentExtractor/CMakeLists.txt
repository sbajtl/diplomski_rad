cmake_minimum_required(VERSION 3.1.0)
set(CMAKE_CXX_STANDARD 17)

project (DocumentExtractor)

set(OUTPUT_DIR ${CMAKE_SYSTEM_NAME})

set(CMAKE_DEBUG_POSTFIX)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
endif()

set(PACKAGE_NAME "DocumentExtractor")

add_definitions(-std=c++17)

set(SRCS
        DocumentExtractor.cc
)

set(HDRS
        DocumentExtractor.h
)

INCLUDE_DIRECTORIES(
   ${CMAKE_SOURCE_DIR}
)

set(EXTRA_LIBS)
set(EXTRA_LIBRARY_PATH)
set(EXTRA_DEPENDENCIES)

link_directories(
  ${EXTRA_LIBRARY_PATH}
)

# Find OpenCV, you may need to set OpenCV_DIR variable
# to the absolute path to the directory containing OpenCVConfig.cmake file
# via the command line or GUI
if(EMSCRIPTEN)
    set(OpenCV_DIR ${CMAKE_SOURCE_DIR}/lib-emscripten/opencv/lib/cmake/opencv4)
else(EMSCRIPTEN)
    set(OpenCV_DIR ${CMAKE_SOURCE_DIR}/lib-macos/opencv/lib/cmake/opencv4)
endif(EMSCRIPTEN)

find_package(OpenCV REQUIRED)

# If the package has been found, several variables will
# be set, you can find the full list with descriptions
# in the OpenCVConfig.cmake file.
# Print some message showing some of them
message(STATUS "OpenCV library status:")
message(STATUS "    config: ${OpenCV_DIR}")
message(STATUS "    version: ${OpenCV_VERSION}")
message(STATUS "    libraries: ${OpenCV_LIBS}")
message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")

include_directories(${OpenCV_INCLUDE_DIRS})

set(LIBS ${OpenCV_LIBS})

if(EMSCRIPTEN)
    include(${CMAKE_SOURCE_DIR}/emscripten/CMakeLists.txt)
else(EMSCRIPTEN)
    add_definitions(-DHAVE_THREADS)
    include(${CMAKE_SOURCE_DIR}/linux/CMakeLists.txt)
endif(EMSCRIPTEN)

ADD_EXECUTABLE(
        DocumentExtractor
        ${EXTRA_DEPENDENCIES} ${SRCS} ${HDRS}
)

TARGET_LINK_LIBRARIES (
        DocumentExtractor
        ${LIBS}
        ${EXTRA_LIBS}
)

