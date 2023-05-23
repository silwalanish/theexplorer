cmake_minimum_required(VERSION 3.15)
project(theexplorer CXX)

find_package(GLFW3 REQUIRED)
find_package(glm REQUIRED)
find_package(GLEW REQUIRED)

add_executable(${PROJECT_NAME} 
        src/core/GameWindow.cpp
        src/core/GLFWContext.cpp
        src/core/GLEWContext.cpp
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
