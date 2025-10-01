cmake_minimum_required(VERSION 3.20)

# Název projektu a standard C++
project(Zakladni_Projekt LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Zdrojáky projektu – uveď všechny .cpp
set(SOURCES
    main.cpp
    Application.cpp
    Model.cpp
    Shader_program.cpp
    Shape.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

# Knihovny
find_package(OpenGL REQUIRED)       # poskytuje target OpenGL::GL
find_package(glfw3 REQUIRED)        # na Ubuntu (libglfw3-dev) poskytuje target glfw
find_package(GLEW REQUIRED)         # poskytuje target GLEW::GLEW

# glm je obvykle header-only. Zkusíme najít config a jinak jen include dir.
find_package(glm QUIET)             # pokud je k dispozici, dá target glm::glm
if(glm_FOUND)
    target_link_libraries(${PROJECT_NAME} PRIVATE glm::glm)
else()
    find_path(GLM_INCLUDE_DIR glm/glm.hpp)
    if(NOT GLM_INCLUDE_DIR)
        message(FATAL_ERROR "GLM not found. Install glm or provide GLM_INCLUDE_DIR.")
    endif()
    target_include_directories(${PROJECT_NAME} PRIVATE ${GLM_INCLUDE_DIR})
endif()

# Linkování hlavních knihoven
target_link_libraries(${PROJECT_NAME}
    PRIVATE
        OpenGL::GL
        glfw
        GLEW::GLEW
)

# (volitelné) Přísnější varování na GCC/Clang/MSVC
if (CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)
elseif (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4 /permissive-)
endif()

# (volitelné) Output dir, ať se binárka ukládá do build/bin
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)
