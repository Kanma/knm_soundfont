cmake_minimum_required(VERSION 3.22)
project(KNM_SOUNDFONT)

option(KNM_SOUNDFONT_BUILD_DOCS "Generate the documentation (default=ON)" ON)
option(KNM_SOUNDFONT_RUN_TESTS  "Run the tests during build (default=ON)" ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(examples)

if (KNM_SOUNDFONT_RUN_TESTS)
    add_subdirectory(tests)
endif()

if (KNM_SOUNDFONT_BUILD_DOCS)
    add_subdirectory(docs)
endif()
