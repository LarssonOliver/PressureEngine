cmake_minimum_required(VERSION 3.0)

project(PressureEngineViewer)

add_executable(PressureEngineViewer Viewer.cpp)

include_directories(${CMAKE_SOURCE_DIR}/PressureEngineCore/Include)
target_link_libraries(PressureEngineViewer PressureEngineCore)

set_target_properties(PressureEngineViewer PROPERTIES FOLDER "PressureEngine")

include_directories(${CMAKE_SOURCE_DIR}/build/PressureEngineCore/Dependencies/glad/include)
include_directories(${CMAKE_SOURCE_DIR}/PressureEngineCore/Dependencies/glfw/include)

add_custom_command(TARGET PressureEngineViewer POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${PROJECT_SOURCE_DIR}/Res
    $<TARGET_FILE_DIR:PressureEngineViewer>/Res)

add_custom_command(TARGET PressureEngineViewer POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${PROJECT_SOURCE_DIR}/Res
    ${PROJECT_BINARY_DIR}/Res)