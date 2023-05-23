cmake_minimum_required(VERSION 3.15)
project(theexplorer CXX)

add_executable(theexplorer src/theexplorer.cpp src/main.cpp)

install(TARGETS theexplorer DESTINATION "."
        RUNTIME DESTINATION bin
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        )
