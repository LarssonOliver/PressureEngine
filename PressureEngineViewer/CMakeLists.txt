cmake_minimum_required(VERSION 3.0)

project(PressureEngineViewer)

add_executable(${PROJECT_NAME} Viewer.cpp)

# Engine core.
include_directories(${CMAKE_SOURCE_DIR}/PressureEngineCore/Include)
target_link_libraries(${PROJECT_NAME} PressureEngineCore)

# Organise project structure.
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER ${CMAKE_PROJECT_NAME})

# include_directories(${CMAKE_SOURCE_DIR}/build/PressureEngineCore/Dependencies/glad/include)
# include_directories(${CMAKE_SOURCE_DIR}/PressureEngineCore/Dependencies/glfw/include)

# Copy resources to exe path.
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${PROJECT_SOURCE_DIR}/Res
    $<TARGET_FILE_DIR:${PROJECT_NAME}>/Res)

if (MSVC) # Needed to find resources when debugging.
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${PROJECT_SOURCE_DIR}/Res
        ${PROJECT_BINARY_DIR}/Res)  
endif()