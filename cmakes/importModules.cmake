add_subdirectory(${CMAKE_SOURCE_DIR}/modules/WidgetManager)
add_subdirectory(${CMAKE_SOURCE_DIR}/modules/WidgetFrame)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
    WidgetManager
    MainWindow
)
