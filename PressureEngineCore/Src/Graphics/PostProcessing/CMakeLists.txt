list(APPEND PRESSURE_SRC
	${CMAKE_CURRENT_SOURCE_DIR}/ImageRenderer.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/PostProcessing.cpp)	
	
	
list(APPEND PRESSURE_HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/ImageRenderer.h
    ${CMAKE_CURRENT_SOURCE_DIR}/PostProcessing.h)


add_subdirectory(Contrast)
add_subdirectory(DepthOfField)
add_subdirectory(LightScattering)

set(PRESSURE_SRC ${PRESSURE_SRC} PARENT_SCOPE)	
set(PRESSURE_HEADERS ${PRESSURE_HEADERS} PARENT_SCOPE)	