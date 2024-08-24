target_sources(${PROJECT_NAME}
    PRIVATE
        includes/game/scripts/EditorCameraController.hpp
        includes/game/scenes/ShowcaseScene.hpp

        src/scripts/EditorCameraController.cpp
        src/scenes/ShowcaseScene.cpp
        src/main.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_LIST_DIR}/includes)
