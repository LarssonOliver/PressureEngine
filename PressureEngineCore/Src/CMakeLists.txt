list(APPEND PRESSURE_SRC
	${CMAKE_CURRENT_SOURCE_DIR}/PressureEngine.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/Callbacks.cpp)	
	
	
list(APPEND PRESSURE_HEADERS
	${CMAKE_CURRENT_SOURCE_DIR}/Callbacks.h
	${CMAKE_CURRENT_SOURCE_DIR}/Common.h
	${CMAKE_CURRENT_SOURCE_DIR}/Constants.h
	${CMAKE_CURRENT_SOURCE_DIR}/DllExport.h)


add_subdirectory(Graphics)
add_subdirectory(Input)
add_subdirectory(Math)
add_subdirectory(Services)

set(PRESSURE_SRC ${PRESSURE_SRC} PARENT_SCOPE)	
set(PRESSURE_HEADERS ${PRESSURE_HEADERS} PARENT_SCOPE)	