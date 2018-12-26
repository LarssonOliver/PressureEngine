

list(APPEND PRESSURE_SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/Math.cpp
    
    ${CMAKE_CURRENT_SOURCE_DIR}/Matrices/Matrix4f.cpp)	
	
	
list(APPEND PRESSURE_HEADERS	
	${CMAKE_CURRENT_SOURCE_DIR}/Math.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Random.h
    
    ${CMAKE_CURRENT_SOURCE_DIR}/Matrices/Matrix4f.h)		
    
add_subdirectory(Geometry)
add_subdirectory(Vectors)

set(PRESSURE_SRC ${PRESSURE_SRC} PARENT_SCOPE)	
set(PRESSURE_HEADERS ${PRESSURE_HEADERS} PARENT_SCOPE)	