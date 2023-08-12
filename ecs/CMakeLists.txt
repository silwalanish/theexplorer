target_sources(${PROJECT_NAME}
    PRIVATE
        includes/ecs/Component.hpp
        includes/ecs/ComponentManager.hpp
        includes/ecs/Entity.hpp
        includes/ecs/Events.hpp
        includes/ecs/EntityManager.hpp
        includes/ecs/World.hpp
        includes/ecs/System.hpp
        includes/ecs/ScopedSystem.hpp
        includes/ecs/components/Camera.hpp
        includes/ecs/components/Transform.hpp
        includes/ecs/components/Mesh.hpp
        includes/ecs/components/Terrain.hpp
        includes/ecs/components/DirectionalLight.hpp
        includes/ecs/systems/TransformSystem.hpp

        src/World.cpp
        src/Entity.cpp
        src/Component.cpp
        src/EntityManager.cpp
        src/System.cpp
        src/components/Transform.cpp
        src/systems/TransformSystem.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_LIST_DIR}/includes)
