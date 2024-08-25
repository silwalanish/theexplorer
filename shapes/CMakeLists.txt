target_sources(${PROJECT_NAME}
    PRIVATE
        includes/shapes/Cube.hpp

        src/Cube.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_LIST_DIR}/includes)
