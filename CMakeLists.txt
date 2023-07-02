cmake_minimum_required(VERSION 3.10)

project(ExampleInterface)

find_package(nlohmann_json REQUIRED)

# Some system may inject Python headers via Toolchain file
if(NOT PythonLibs_FOUND)
    find_package(PythonLibs REQUIRED)
endif()

find_package(PythonInterp)
find_package(Python)

include_directories(include ${PYTHON_INCLUDE_DIRS})

add_library(Fractal SHARED module/FractalModule.cpp)


target_link_libraries(Fractal ${PYTHON_LIBRARIES} nlohmann_json::nlohmann_json)

set_target_properties(
    Fractal
        PROPERTIES
        PREFIX ""
        OUTPUT_NAME "Fractal"
        LINKER_LANGUAGE CXX
    )