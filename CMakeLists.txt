cmake_minimum_required(VERSION 3.16)

if(NOT DEFINED ENV{EMSDK} AND EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/.emsdk")
    set(ENV{EMSDK} "${CMAKE_CURRENT_SOURCE_DIR}/.emsdk")
endif()

project(LEVEL_EDITOR)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)

# Appends the cmake/ path inside CMAKE_MODULE_PATH
set(CMAKE_MODULE_PATH ${LEVEL_EDITOR_SOURCE_DIR}/cmake/ ${CMAKE_MODULE_PATH})

# Globally include every cpp/hpp/h file recursively if it is in the src dir
file(GLOB_RECURSE EDITOR_SRC CONFIGURE_DEPENDS "src/*/*.h" "src/*/*.hpp" "src/*/*.cpp")
set(ALL_SRC src/Main.cpp ${EDITOR_SRC})

# HighFive options
set(HIGHFIVE_EXAMPLES FALSE CACHE INTERNAL "")
set(HIGHFIVE_UNIT_TESTS FALSE CACHE INTERNAL "")
set(HIGHFIVE_USE_EIGEN FALSE)
set(HIGHFIVE_USE_BOOST OFF CACHE BOOL "" FORCE)

add_subdirectory(ext/HighFive)
include_directories("ext/HighFive/include")

if(EMSCRIPTEN)
    if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/.hdf5-wasm/lib/libhdf5.a")
        message(STATUS "Downloading and extracting prebuilt HDF5 WebAssembly libraries...")
        file(MAKE_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/.hdf5-wasm")
        if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/.hdf5-wasm/hdf5.tar.gz")
            file(DOWNLOAD
                "https://github.com/usnistgov/libhdf5-wasm/releases/download/v0.5.0_3.1.68/HDF5-1.14.6-Emscripten.tar.gz"
                "${CMAKE_CURRENT_SOURCE_DIR}/.hdf5-wasm/hdf5.tar.gz"
                EXPECTED_HASH SHA256=90c26256f3d1fd0b421b7e0defebe1894f179b2a50252aeb059aaa1fa6bdb7e9
                SHOW_PROGRESS
            )
        endif()
        execute_process(
            COMMAND ${CMAKE_COMMAND} -E tar xzf "${CMAKE_CURRENT_SOURCE_DIR}/.hdf5-wasm/hdf5.tar.gz"
            WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/.hdf5-wasm"
        )
    endif()

    find_package(Qt6 COMPONENTS Core Gui Widgets Multimedia REQUIRED)

    set(HDF5_WASM_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/.hdf5-wasm/include")
    set(HDF5_WASM_LIBS
        "${CMAKE_CURRENT_SOURCE_DIR}/.hdf5-wasm/lib/libhdf5_hl.a"
        "${CMAKE_CURRENT_SOURCE_DIR}/.hdf5-wasm/lib/libhdf5.a"
        "${CMAKE_CURRENT_SOURCE_DIR}/.hdf5-wasm/lib/libszaec.a"
        "${CMAKE_CURRENT_SOURCE_DIR}/.hdf5-wasm/lib/libaec.a"
        "${CMAKE_CURRENT_SOURCE_DIR}/.hdf5-wasm/lib/libzlib-static.a"
    )

    include_directories(${HDF5_WASM_INCLUDE_DIR})

    add_executable(editor ${ALL_SRC})
    target_link_libraries(editor PRIVATE
        Qt6::Core Qt6::Gui Qt6::Widgets Qt6::Multimedia
        ${HDF5_WASM_LIBS}
    )

    target_link_options(editor PRIVATE
        "-sALLOW_MEMORY_GROWTH=1"
        "-sNO_EXIT_RUNTIME=1"
        "-sASYNCIFY=1"
        "--pre-js=${CMAKE_CURRENT_SOURCE_DIR}/web/audio_patch.js"
    )


    if(COMMAND qt_finalize_executable)
        qt_finalize_executable(editor)
    endif()

    configure_file("${CMAKE_CURRENT_SOURCE_DIR}/web/editor.html"
        "${CMAKE_CURRENT_BINARY_DIR}/editor.html" COPYONLY)
    configure_file("${CMAKE_CURRENT_SOURCE_DIR}/web/editor.html"
        "${CMAKE_CURRENT_BINARY_DIR}/index.html" COPYONLY)
else()
    # Native Qt6 build
    if(APPLE AND NOT DEFINED CMAKE_PREFIX_PATH)
        list(APPEND CMAKE_PREFIX_PATH "/opt/homebrew/opt/qt" "/usr/local/opt/qt")
    endif()

    find_package(Qt6 COMPONENTS Core Gui Widgets Multimedia REQUIRED)

    find_package(HDF5 REQUIRED COMPONENTS C CXX HL)
    include_directories(${HDF5_INCLUDE_DIRS})

    add_executable(editor ${ALL_SRC})
    target_link_libraries(editor PRIVATE m ${HDF5_LIBRARIES} ${HDF5_HL_LIBRARIES} Qt6::Core Qt6::Gui Qt6::Widgets Qt6::Multimedia)
endif()

add_custom_target(style astyle --style=allman --pad-oper --pad-comma ${CMAKE_SOURCE_DIR}/src/*)