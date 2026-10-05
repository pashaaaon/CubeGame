cmake_minimum_required(VERSION 3.15)
project(CubeGame)

add_executable(CubeGame ${PROJECT_SOURCE_DIR}/CubeGame.cpp)

target_include_directories(CubeGame PRIVATE 
    ${PROJECT_SOURCE_DIR}/Engine/External/glad/include 
    ${PROJECT_SOURCE_DIR}/Engine/External/glfw-3.4/include 
    ${PROJECT_SOURCE_DIR}/Engine/External/glm-1.0.3/glm 
    ${PROJECT_SOURCE_DIR}/Engine/External/stb_image
)

target_link_libraries(CubeGame 
    opengl32 
    ${PROJECT_SOURCE_DIR}/Engine/External/glad/src/libglad.a 
    ${PROJECT_SOURCE_DIR}/Engine/External/glfw-3.4/lib-mingw-w64/libglfw3.a
)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static -static-libgcc -static-libstdc++")
set_target_properties(CubeGame PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/CubeGame-bin)

add_custom_target(CopyResources ALL 
    COMMAND ${CMAKE_COMMAND} -E copy_directory "${PROJECT_SOURCE_DIR}/Engine/Shaders" "${PROJECT_SOURCE_DIR}/CubeGame-bin/Shaders"
    COMMAND ${CMAKE_COMMAND} -E copy_directory "${PROJECT_SOURCE_DIR}/Content" "${PROJECT_SOURCE_DIR}/CubeGame-bin/Content"
)
