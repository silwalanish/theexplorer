cmake_minimum_required(VERSION 3.15)
project(theexplorer CXX)

find_package(GLFW3 REQUIRED)
find_package(glm REQUIRED)
find_package(GLEW REQUIRED)

add_executable(${PROJECT_NAME} 
        includes/systems/SceneRenderer.hpp
        includes/systems/DebugRenderer.hpp
        
        includes/scripts/EditorCameraController.hpp
        includes/scripts/TerrainGenerator.hpp

        includes/opengl/VertexArray.hpp
        includes/opengl/Shader.hpp

        includes/shaders/BasicShader.hpp
        includes/shaders/DebugShader.hpp

        includes/utils/Math.hpp

        includes/terrain/HeightMap.hpp

        includes/game/ShowcaseScene.hpp

        src/systems/SceneRenderer.cpp
        src/systems/DebugRenderer.cpp
        
        src/scripts/EditorCameraController.cpp
        src/scripts/TerrainGenerator.cpp

        src/opengl/VertexArray.cpp
        src/opengl/Shader.cpp

        src/shaders/BasicShader.cpp
        src/shaders/DebugShader.cpp

        src/utils/Math.cpp

        src/terrain/HeightMap.cpp

        src/game/ShowcaseScene.cpp

        src/main.cpp
)

add_subdirectory(core)
add_subdirectory(ecs)
add_subdirectory(scripting)

target_compile_definitions(${PROJECT_NAME} PRIVATE GLFW_INCLUDE_NONE)
target_include_directories(${PROJECT_NAME} PRIVATE includes)
target_link_libraries(${PROJECT_NAME} glfw glm::glm GLEW::GLEW)

install(TARGETS ${PROJECT_NAME} DESTINATION "."
        RUNTIME DESTINATION bin
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
)
