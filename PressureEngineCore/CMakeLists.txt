cmake_minimum_required(VERSION 3.0)

project(PressureEngineCore)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

# List of all sources, will be modified in subdirs before add_library.
set(PRESSURE_SRC)
set(PRESSURE_HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/Include/${PROJECT_NAME}/PressureEngine.h)

include_directories(Include)

# Will find all sources and save them in 
# PRESSURE_SRC AND PRESSURE_HEADERS respectively.
add_subdirectory(Src)

# VS solution organisation.
assign_source_group(${PRESSURE_SRC})
assign_source_group(${PRESSURE_HEADERS})

# Symbol visibility.
add_definitions(-DPRESSURE_EXPORTS)

add_library(${PROJECT_NAME} SHARED ${PRESSURE_SRC} ${PRESSURE_HEADERS}) 

# Add and link dependencies.
# GLFW
add_subdirectory(Dependencies/glfw)
target_link_libraries(${PROJECT_NAME} glfw)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/glfw/include)


# GLAD & OpenGL
add_subdirectory(Dependencies/glad)
target_link_libraries(${PROJECT_NAME} glad)
target_link_libraries(${PROJECT_NAME} opengl32.lib)
include_directories(${PROJECT_BINARY_DIR}/Dependencies/glad/include)

# Solution organisation.
set_target_properties(glad PROPERTIES FOLDER "GLAD")
set_target_properties(glad-generate-files PROPERTIES FOLDER "GLAD")

# FreeImage
add_library(FreeImage STATIC IMPORTED)
set_property(TARGET FreeImage PROPERTY IMPORTED_LOCATION
    ${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/FreeImage/lib/FreeImage.lib)
target_link_libraries(${PROJECT_NAME} FreeImage)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/FreeImage/include)

# Debug define.
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DPRESSURE_DEBUG")

# Copy dll into bin folder after build.
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/FreeImage/lib/FreeImage.dll
    $<TARGET_FILE_DIR:${PROJECT_NAME}>)

# Solution organisation.
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER ${CMAKE_PROJECT_NAME})