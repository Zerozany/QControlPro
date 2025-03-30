file(GLOB DIRS LIST_DIRECTORIES true ${CMAKE_CURRENT_SOURCE_DIR}/*)

set(ALL_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR})  

foreach(dir ${DIRS})
    if(IS_DIRECTORY ${dir})
        file(GLOB HEADER_FILES ${dir}/*.h)
        file(GLOB SOURCE_FILES ${dir}/*.cpp)
        target_sources(${PROJECT_NAME} 
            PRIVATE 
            ${HEADER_FILES} 
            ${SOURCE_FILES}
        )
        list(APPEND ALL_INCLUDE_DIRS ${dir})
    endif()
endforeach()

target_include_directories(${PROJECT_NAME} PRIVATE ${ALL_INCLUDE_DIRS})
