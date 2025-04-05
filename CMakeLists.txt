cmake_minimum_required(VERSION 3.25 FATAL_ERROR)

set(CMAKE_TOOLCHAIN_FILE "D:/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")

set(VCPKG_TARGET_TRIPLET "x64-windows" CACHE STRING "Static link dynamic call")

project(QControlPro VERSION 1.0.0 LANGUAGES CXX)

add_executable(${PROJECT_NAME}
    ${PROJECT_SOURCE_DIR}/source/src/main.cpp
)

include(${PROJECT_SOURCE_DIR}/cmakes/importQt.cmake)
include(${PROJECT_SOURCE_DIR}/cmakes/importO3rd.cmake)
include(${PROJECT_SOURCE_DIR}/cmakes/importSources.cmake)
include(${PROJECT_SOURCE_DIR}/cmakes/importModules.cmake)

target_compile_features(${PROJECT_NAME}
    PRIVATE
    cxx_std_23
)
