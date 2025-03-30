find_package(spdlog CONFIG REQUIRED)
find_package(toml11 CONFIG REQUIRED)
find_package(FFMPEG REQUIRED)

target_include_directories(${PROJECT_NAME}
    PRIVATE
    ${FFMPEG_INCLUDE_DIRS}
)

target_link_directories(${PROJECT_NAME}
    PRIVATE
    ${FFMPEG_LIBRARY_DIRS}
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
    spdlog::spdlog
    toml11::toml11
    ${FFMPEG_LIBRARIES}
)
