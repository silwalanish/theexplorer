target_sources(${PROJECT_NAME}
    PRIVATE
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
        includes/core/Light.hpp
        includes/core/EntityHandle.hpp
        includes/core/EntityManager.hpp
        includes/core/utils/Math.hpp

        src/GameWindow.cpp
        src/GLFWContext.cpp
        src/GLEWContext.cpp
        src/Application.cpp
        src/Event.cpp
        src/Scene.cpp
        src/SceneGraph.cpp
        src/Input.cpp
        src/MeshData.cpp
        src/EntityManager.cpp
        src/utils/Math.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_LIST_DIR}/includes)
