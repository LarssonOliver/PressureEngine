cmake_minimum_required(VERSION 3.0)

project(PressureEngineCore)

set(PRESSURE_SRC
    Src/PressureEngine.cpp)

set(PRESSURE_HEADERS
    Include/PressureEngineCore/PressureEngine.h)

include_directories(Include)

add_subdirectory(Src)

assign_source_group(${PRESSURE_SRC})
assign_source_group(${PRESSURE_HEADERS})

add_definitions(-DPRESSURE_EXPORTS)

add_library(PressureEngineCore SHARED ${PRESSURE_SRC} ${PRESSURE_HEADERS}) 

add_subdirectory(Dependencies/glfw)
target_link_libraries(PressureEngineCore glfw)
include_directories(Dependencies/glfw/include)

add_subdirectory(Dependencies/glad)
target_link_libraries(PressureEngineCore glad)
target_link_libraries(PressureEngineCore opengl32.lib)
include_directories(${CMAKE_SOURCE_DIR}/build/${PROJECT_NAME}/Dependencies/glad/include)
set_target_properties(glad PROPERTIES FOLDER "GLAD")
set_target_properties(glad-generate-files PROPERTIES FOLDER "GLAD")

add_library(FreeImage STATIC IMPORTED)
set_property(TARGET FreeImage PROPERTY IMPORTED_LOCATION ${PROJECT_SOURCE_DIR}/Dependencies/FreeImage/lib/FreeImage.lib)
target_link_libraries(PressureEngineCore FreeImage)
include_directories(Dependencies/FreeImage/include)
add_custom_command(TARGET PressureEngineCore POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${PROJECT_SOURCE_DIR}/Dependencies/FreeImage/bin
    $<TARGET_FILE_DIR:PressureEngineCore>)

set_target_properties(PressureEngineCore PROPERTIES FOLDER "PressureEngine")