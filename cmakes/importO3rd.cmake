find_package(spdlog CONFIG REQUIRED)
find_package(toml11 CONFIG REQUIRED)
find_package(FFmpeg REQUIRED)

target_include_directories(${PROJECT_NAME}
    PUBLIC
    ${FFMPEG_INCLUDE_DIRS}
)

target_link_directories(${PROJECT_NAME}
    PUBLIC
    ${FFMPEG_LIBRARY_DIRS}
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
    spdlog::spdlog
    toml11::toml11
    ${FFMPEG_LIBRARIES}
)
