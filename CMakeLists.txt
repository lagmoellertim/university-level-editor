project(LEVEL_EDITOR)
set(CMAKE_AUTOMOC ON)

# States that CMake required version must be greater than 2.8
cmake_minimum_required(VERSION 3.12)

# Currently we are only using c++11 features.
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
set(CMAKE_CXX_FLAGS_DEBUG "-Wall -g")


# Appends the cmake/modules path inside the MAKE_MODULE_PATH variable which stores the
# directories of additional CMake modules (ie. MacroOutOfSourceBuild.cmake):
set(CMAKE_MODULE_PATH ${LEVEL_EDITOR_SOURCE_DIR}/cmake/ ${CMAKE_MODULE_PATH})


# Globally Include every cpp/hpp/h file recursively if it is in the src dir
file(GLOB_RECURSE EDITOR_SRC CONFIGURE_DEPENDS "src/*/*.h" "src/*/*.hpp" "src/*/*.cpp")

# Find SDL2 libraries using the custom made module in
# the cmake/ path
find_package(SDL2 REQUIRED)
find_package(SDL2_IMAGE REQUIRED)
find_package(Qt5 COMPONENTS Widgets Multimedia REQUIRED)

# Find required boost libraries
find_package(Boost 1.54 COMPONENTS filesystem system REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

# Find and add HighFive
set(HIGHFIVE_EXAMPLES FALSE CACHE INTERNAL "")
set(HIGHFIVE_UNIT_TESTS FALSE CACHE INTERNAL "")
set(HIGHFIVE_USE_EIGEN FALSE)
set(HIGHFIVE_USE_BOOST ON CACHE BOOL "" FORCE)

add_subdirectory(ext/HighFive)
include_directories("ext/HighFive/include")
find_package(HDF5 REQUIRED COMPONENTS C CXX HL)
include_directories(${HDF5_INCLUDE_DIRS})

# Add SDL2 include directory to search path
include_directories(${SDL2_INCLUDE_DIR})
include_directories(${SDL2_IMG_INCLUDE_DIR})

# Build executable
add_executable(editor src/Main.cpp ${EDITOR_SRC})
target_link_libraries(editor ${SDL2_LIBRARY} ${SDL2_IMG_LIBRARY})
target_link_libraries(editor m)
target_link_libraries(editor ${Boost_LIBRARIES})
target_link_libraries(editor ${HDF5_LIBRARIES} ${HDF5_HL_LIBRARIES})
target_link_libraries(editor Qt5::Core Qt5::Gui Qt5::Widgets Qt5::Multimedia)

add_custom_target(style astyle --style=allman --pad-oper --pad-comma ${CMAKE_SOURCE_DIR}/src/*)