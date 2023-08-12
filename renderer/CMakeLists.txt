target_sources(${PROJECT_NAME}
    PRIVATE
        includes/renderer/opengl/VertexArray.hpp
        includes/renderer/opengl/Shader.hpp
        includes/renderer/shaders/BasicShader.hpp
        includes/renderer/shaders/DebugShader.hpp
        includes/renderer/SceneRenderer.hpp
        includes/renderer/DebugRenderer.hpp
        includes/renderer/RenderableScene.hpp

        src/opengl/VertexArray.cpp
        src/opengl/Shader.cpp
        src/shaders/BasicShader.cpp
        src/shaders/DebugShader.cpp
        src/SceneRenderer.cpp
        src/DebugRenderer.cpp
        src/RenderableScene.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_LIST_DIR}/includes)
