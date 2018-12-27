list(APPEND PRESSURE_SRC
	${CMAKE_CURRENT_SOURCE_DIR}/Loader.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/MasterRenderer.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/OBJLoader.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/Window.cpp)	
	
	
list(APPEND PRESSURE_HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/GraphicsCommon.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Loader.h
    ${CMAKE_CURRENT_SOURCE_DIR}/MasterRenderer.h
    ${CMAKE_CURRENT_SOURCE_DIR}/OBJLoader.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Window.h)

	
add_subdirectory(Entities)
add_subdirectory(EntityShaders)
add_subdirectory(GLObjects)
add_subdirectory(Guis)
add_subdirectory(Models)
add_subdirectory(Particles)
add_subdirectory(PostProcessing)
add_subdirectory(Shaders)
add_subdirectory(Shadows)
add_subdirectory(Skybox)
add_subdirectory(Textures)
add_subdirectory(Water)

set(PRESSURE_SRC ${PRESSURE_SRC} PARENT_SCOPE)	
set(PRESSURE_HEADERS ${PRESSURE_HEADERS} PARENT_SCOPE)	