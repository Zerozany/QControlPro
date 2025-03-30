file(GLOB SOURCE_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

set(MODEL_NAME MainWindow)

add_library(${MODEL_NAME} STATIC ${SOURCE_FILES})

target_compile_features(${MODEL_NAME}
    PRIVATE
    cxx_std_23
)

set_target_properties(${MODEL_NAME} PROPERTIES
    AUTOUIC ON
    AUTOMOC ON
    AUTORCC ON
)

target_include_directories(${MODEL_NAME}
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

target_link_libraries(${MODEL_NAME}
    PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Core
)
