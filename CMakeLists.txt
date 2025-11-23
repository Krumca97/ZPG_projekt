cmake_minimum_required(VERSION 3.20)

# Název projektu a standard C++
project(Projekt LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Zdrojáky projektu 
set(SOURCES
    main.cpp
    Application.cpp
    DrawAbleObject.cpp
    Shader_program.cpp
    Shader.cpp
    Model.cpp
    Scene.cpp
    Transformations/TransformationComponent.h
    Transformations/TransformationRotate.cpp
    Transformations/TransformationScale.cpp
    Transformations/TransformationTranslate.cpp
    Transformations/TransformationComposite.cpp
    CameraSubject.cpp
    Controller.cpp
    LightSubject.cpp
    Lights/AmbientLight.cpp
    Lights/DirectionalLight.cpp
    Lights/PointLight.cpp
    Lights/SpotLight.cpp
    Libraries/tiny_obj_loader.h
    Material.cpp
    Libraries/stb_image.h
    TextureLoader.cpp
    Skybox.cpp
    Transformations/TransformationCustom.cpp
    Transformations/TransformationPath.cpp
    Scenes/Scene1.cpp
    Scenes/Scene2.cpp
    Scenes/Scene3.cpp
    Scenes/Scene4.cpp
    Scenes/Scene5.cpp
    Scenes/Scene6.cpp
    Scenes/Scene7.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

# Knihovny
find_package(OpenGL REQUIRED)       
find_package(glfw3 REQUIRED)        
find_package(GLEW REQUIRED)        

# glm je obvykle header-only. 
find_package(glm QUIET)            
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

#Varovani a debugg
if (CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)
elseif (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4 /permissive-)
endif()

# output do /bin
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)