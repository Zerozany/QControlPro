add_subdirectory(${CMAKE_SOURCE_DIR}/views)

file(GLOB SOURCE_FILES
    ${CMAKE_SOURCE_DIR}/include/*.h
    ${CMAKE_SOURCE_DIR}/src/*.cpp
)

file(GLOB RESOURCES_LIST
    RELATIVE ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/resources/css/*
    ${CMAKE_SOURCE_DIR}/resources/icon/*
    ${CMAKE_SOURCE_DIR}/resources/application/*
)

target_sources(${PROJECT_NAME}
    PRIVATE
    ${SOURCE_FILES}
    ${CMAKE_SOURCE_DIR}/resources/application/appicon.rc
)

qt_add_resources(${PROJECT_NAME}
    PREFIX "/"
    FILES
    ${RESOURCES_LIST}
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)
