add_definitions(-Wno-potentially-evaluated-expression)

if (CMAKE_BUILD_TYPE MATCHES Release)
    message("Release mode")
else (CMAKE_BUILD_TYPE)
    add_definitions(-DEMCC_DEBUG=1)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g4")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g4")
endif ()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/emscripten)
set(IDLS ${CMAKE_SOURCE_DIR}/emscripten/interfaces.idl)
set(STUB emscripten/glue_stub.cc)
set(GLUE_COMMAND python3)

set(GLUE_SCRIPT ${CMAKE_SOURCE_DIR}/emsdk/upstream/emscripten/tools/webidl_binder.py)

function(create_glue out_var)
    set(result)
    foreach (in_f ${ARGN})
        file(RELATIVE_PATH out_f ${CMAKE_CURRENT_SOURCE_DIR} ${in_f})
        STRING(REGEX REPLACE "\\.idl" _glue out_f "${out_f}")
        set(glue_f "${CMAKE_CURRENT_SOURCE_DIR}/${out_f}.js")
        set(out_f "${CMAKE_CURRENT_SOURCE_DIR}/${out_f}")
        set_source_files_properties(
                ${glue_f}
                PROPERTIES
                GENERATED TRUE
        )
        add_custom_command(OUTPUT ${out_f}.js
                COMMAND ${GLUE_COMMAND} ${GLUE_SCRIPT} ${in_f} ${out_f} glue
                DEPENDS ${in_f}
                WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
                COMMENT "Creating file ${out_f}"
                VERBATIM
                )
        list(APPEND result ${glue_f})
    endforeach ()
    set(${out_var} "${result}" PARENT_SCOPE)
endfunction()

create_glue(glue_files ${IDLS})

SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -std=c++17 --bind \
-s ASSERTIONS=1 \
-s DISABLE_EXCEPTION_CATCHING=0 \
-s SINGLE_FILE=1 \
-s WASM=1 \
-s ALLOW_MEMORY_GROWTH=1 \
-s NO_FILESYSTEM=1 \
-s ELIMINATE_DUPLICATE_FUNCTIONS=1 \
-s NO_EXIT_RUNTIME=1 \
-O3 --post-js ${glue_files}")

list(APPEND SRCS
        emscripten/Extractor.cc
        ${STUB}
        )

list(APPEND HDRS
        emscripten/Extractor.h
        )

add_custom_target(
        generate_glue ALL
        DEPENDS ${glue_files}
)

set(INTERFACES_GLUE ${CMAKE_SOURCE_DIR}/emscripten/interfaces_glue.cpp)
set_source_files_properties(${INTERFACES_GLUE} PROPERTIES GENERATED TRUE)

add_custom_target(
        generate_bc ALL
        DEPENDS ${INTERFACES_GLUE}
)

add_custom_target(
        generate_program ALL
        DEPENDS ${prep_files}
)

add_dependencies(generate_bc generate_glue)
add_dependencies(generate_program generate_glue)

install(FILES
        ${CMAKE_SOURCE_DIR}/emscripten/interfaces_glue.js
        ${CMAKE_SOURCE_DIR}/emscripten/DocumentExtractor.js
        DESTINATION ${CMAKE_INSTALL_PREFIX}
        )