add_executable(unittests main.cpp)

target_include_directories(unittests
    PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>
)

target_compile_definitions(unittests
    PRIVATE
        DATA_DIR="${CMAKE_CURRENT_LIST_DIR}/data/"
)

# Run the unit tests
if (KNM_SOUNDFONT_RUN_TESTS)
    add_custom_target(run-unittests
        ALL
        unittests
        DEPENDS unittests
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMENT "Unit testing..." VERBATIM
    )
endif()
