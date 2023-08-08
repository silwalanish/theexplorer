target_sources(${PROJECT_NAME}
    PRIVATE
        includes/scripting/Script.hpp
        includes/scripting/ScriptableWorld.hpp
        includes/scripting/ScriptableEntity.hpp
        includes/scripting/NativeScriptEngine.hpp
        includes/scripting/component/NativeScript.hpp

        src/Script.cpp
        src/ScriptableWorld.cpp
        src/ScriptableEntity.cpp
        src/NativeScriptEngine.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_LIST_DIR}/includes)
