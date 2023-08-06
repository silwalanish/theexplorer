cmake_minimum_required(VERSION 3.15)
project(theexplorer CXX)

find_package(GLFW3 REQUIRED)
find_package(glm REQUIRED)
find_package(GLEW REQUIRED)

add_executable(${PROJECT_NAME} 
        includes/core/Application.hpp
        includes/core/GameWindow.hpp
        includes/core/Event.hpp
        includes/core/Events.hpp
        includes/core/EventBus.hpp
        includes/core/GLFWContext.hpp
        includes/core/GLFWContext.hpp
        includes/core/Scene.hpp
        includes/core/SceneGraph.hpp
        includes/core/Vertex.hpp
        includes/core/MeshData.hpp
        includes/core/Material.hpp
        includes/core/KeyCodes.hpp
        includes/core/Input.hpp
        includes/core/Script.hpp
        includes/core/Light.hpp
        
        includes/components/Camera.hpp
        includes/components/Transform.hpp
        includes/components/Mesh.hpp
        includes/components/NativeScript.hpp
        includes/components/Terrain.hpp
        includes/components/DirectionalLight.hpp

        includes/systems/SceneRenderer.hpp
        includes/systems/DebugRenderer.hpp
        includes/systems/TransformSystem.hpp
        includes/systems/Scripting.hpp
        
        includes/scripts/EditorCameraController.hpp
        includes/scripts/TerrainGenerator.hpp

        includes/opengl/VertexArray.hpp
        includes/opengl/Shader.hpp

        includes/shaders/BasicShader.hpp
        includes/shaders/DebugShader.hpp

        includes/ecs/Component.hpp
        includes/ecs/ComponentManager.hpp
        includes/ecs/Entity.hpp
        includes/ecs/EntityHandle.hpp
        includes/ecs/Events.hpp
        includes/ecs/EntityManager.hpp
        includes/ecs/World.hpp
        includes/ecs/System.hpp
        includes/ecs/ScopedSystem.hpp

        includes/utils/Math.hpp

        includes/terrain/HeightMap.hpp

        includes/game/ShowcaseScene.hpp

        src/core/GameWindow.cpp
        src/core/GLFWContext.cpp
        src/core/GLEWContext.cpp
        src/core/Application.cpp
        src/core/Event.cpp
        src/core/Scene.cpp
        src/core/SceneGraph.cpp
        src/core/Input.cpp
        src/core/Script.cpp
        src/core/MeshData.cpp

        src/components/Transform.cpp

        src/ecs/World.cpp
        src/ecs/Entity.cpp
        src/ecs/Component.cpp
        src/ecs/EntityManager.cpp
        src/ecs/System.cpp

        src/systems/SceneRenderer.cpp
        src/systems/DebugRenderer.cpp
        src/systems/TransformSystem.cpp
        src/systems/Scripting.cpp
        
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

target_compile_definitions(${PROJECT_NAME} PRIVATE GLFW_INCLUDE_NONE)
target_include_directories(${PROJECT_NAME} PRIVATE includes)
target_link_libraries(${PROJECT_NAME} glfw glm::glm GLEW::GLEW)

install(TARGETS ${PROJECT_NAME} DESTINATION "."
        RUNTIME DESTINATION bin
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
)
