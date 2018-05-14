cmake_minimum_required(VERSION 3.5)

set(NAME Bomberman)

project(${NAME})

SET(CMAKE_CXX_STANDARD 11)

if (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")
elseif (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wc++11-extensions")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

find_package(glm REQUIRED)
find_package(OpenGL REQUIRED)
find_package(PNG REQUIRED)
find_package(OpenAL REQUIRED)
find_package(LibSndFile REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(assimp 4.1.0 REQUIRED)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(dependencies/glfw)
set(GLFW3_LIBRARY glfw)
set(GLFW3_INCLUDE_DIR dependencies/glfw/include)

set(BUILD_UTILS OFF CACHE BOOL "" FORCE)
add_subdirectory(dependencies/glew/build/cmake)
set(GLEW_LIBRARY glew)
set(GLEW_INCLUDE_DIR dependencies/glew/include)

add_subdirectory(dependencies/tinyobjloader)
set(TINYOBJLOADER_LIBRARY tinyobjloader)
set(TINYOBJLOADER_INCLUDE_DIR dependencies/tinyobjloader)

set(JSON_INCLUDE_DIRS dependencies/json/single_include)

set(STB_INCLUDE_DIR dependencies/stb)

set(SOURCES
        sources/
        dependencies/sigslot/src/signal.cpp
        sources/Game/SceneMain.cpp
        sources/Game/Components/CameraController.cpp
        sources/Game/Components/InGameMenu.cpp
        sources/Game/Components/Bomb.cpp
        sources/Game/Components/InputsMenu.cpp
        sources/Game/Components/Settings.cpp
        sources/Game/Components/MainMenu.cpp
        sources/Game/Components/Character.cpp
        sources/Game/Components/GameManager.cpp
        sources/Game/Components/Breakable.cpp
        sources/Game/Components/Player.cpp
        sources/Game/Components/Item.cpp
        sources/Game/Components/MouseRayTest.cpp
        sources/Game/Components/IA.cpp
        sources/Game/Components/SettingsMenu.cpp
        sources/Game/Components/BackgroundDrawer.cpp
        sources/Game/Components/UIThemeManager.cpp
        sources/Game/Components/BeerRoutineTester.cpp
        sources/Game/Components/Map.cpp
        sources/Game/Input.cpp
        sources/Game/Assets.cpp
        sources/Game/SceneTest.cpp
        sources/Game/CameraTest.cpp
        sources/main.cpp
        sources/Core/Mathf.cpp
        sources/Core/Camera.cpp
        sources/Core/Window.cpp
        sources/Core/Json/JsonSerializable.cpp
        sources/Core/Json/Json.cpp
        sources/Core/GameObject.cpp
        sources/Core/IO/FileUtils.cpp
        sources/Core/Audio/AudioListener.cpp
        sources/Core/Audio/AudioClip.cpp
        sources/Core/Audio/AudioSource.cpp
        sources/Core/Graphics/AMaterial.cpp
        sources/Core/Graphics/Lights/ALight.cpp
        sources/Core/Graphics/Texture.cpp
        sources/Core/Graphics/Graphics.cpp
        sources/Core/Graphics/Mesh.cpp
        sources/Core/Graphics/ShaderProgram.cpp
        sources/Core/Graphics/MeshBuilder.cpp
        sources/Core/Time.cpp
        sources/Core/SceneManager.cpp
        sources/Core/Input.cpp
        sources/Core/Physics/Physics.cpp
        sources/Core/BeerRoutine/ARoutineRunner.cpp
        sources/Core/BeerRoutine/BeerRoutine.cpp
        sources/Core/AScene.cpp
        sources/Core/Transform.cpp
        sources/Core/Component/BoxCollider2D.cpp
        sources/Core/Component/ModelRenderer.cpp
        sources/Core/Component/MeshRenderer.cpp
        sources/Core/Component/Component.cpp
        sources/Core/Component/ACollider.cpp
        sources/Core/Component/ParticleBase.cpp
        sources/Core/Component/CircleCollider.cpp
        sources/Core/Component/RaysRenderer.cpp
        sources/Core/Component/ParticleExplode.cpp
        sources/Core/Component/RigidBody2D.cpp
        sources/Core/Graphics/Lights/DirectionalLight.cpp)

set(HEADERS
        include/
        dependencies/sigslot/src/signal.h
        include/Game/Components/BackgroundDrawer.hpp
        include/Game/Components/Item.hpp
        include/Game/Components/Character.hpp
        include/Game/Components/CameraController.hpp
        include/Game/Components/SettingsMenu.hpp
        include/Game/Components/Breakable.hpp
        include/Game/Components/GameManager.hpp
        include/Game/Components/Settings.hpp
        include/Game/Components/BeerRoutineTester.hpp
        include/Game/Components/Map.hpp
        include/Game/Components/MainMenu.hpp
        include/Game/Components/InputsMenu.hpp
        include/Game/Components/IA.hpp
        include/Game/Components/Bomb.hpp
        include/Game/Components/UIThemeManager.hpp
        include/Game/Components/Player.hpp
        include/Game/Components/MouseRayTest.hpp
        include/Game/Components/InGameMenu.hpp
        include/Game/SceneTest.hpp
        include/Game/SceneMain.hpp
        include/Game/CameraTest.hpp
        include/Game/Assets.hpp
        include/Game/Input.hpp
        include/Game/Game.hpp
        include/Core/Camera.hpp
        include/Core/Mathf.hpp
        include/Core/GameObject.hpp
        include/Core/Time.hpp
        include/Core/Json/Json.hpp
        include/Core/Json/JsonSerializable.hpp
        include/Core/IO/FileUtils.hpp
        include/Core/Audio
        include/Core/Audio/AudioListener.hpp
        include/Core/Audio/AudioClip.hpp
        include/Core/Audio/AudioSource.hpp
        include/Core/Graphics/AMaterial.hpp
        include/Core/Graphics/Lights/ALight.hpp
        include/Core/Graphics/Texture.hpp
        include/Core/Graphics/ShaderProgram.hpp
        include/Core/Graphics/Mesh.hpp
        include/Core/Graphics/Graphics.hpp
        include/Core/Graphics/MeshBuilder.hpp
        include/Core/Window.hpp
        include/Core/Physics/Physics.hpp
        include/Core/BeerRoutine/BeerRoutine.hpp
        include/Core/BeerRoutine/ARoutineRunner.hpp
        include/Core/KeyCode.hpp
        include/Core/AScene.hpp
        include/Core/Input.hpp
        include/Core/BeerEngine.hpp
        include/Core/Core.hpp
        include/Core/Transform.hpp
        include/Core/Component/RigidBody2D.hpp
        include/Core/Component/Component.hpp
        include/Core/Component/IRender.hpp
        include/Core/Component/IColliderStay.hpp
        include/Core/Component/ITriggerExit.hpp
        include/Core/Component/IColliderEnter.hpp
        include/Core/Component/BoxCollider2D.hpp
        include/Core/Component/RaysRenderer.hpp
        include/Core/Component/IRenderAlpha.hpp
        include/Core/Component/ACollider.hpp
        include/Core/Component/IUI.hpp
        include/Core/Component/IColliderExit.hpp
        include/Core/Component/MeshRenderer.hpp
        include/Core/Component/ITriggerEnter.hpp
        include/Core/Component/ParticleExplode.hpp
        include/Core/Component/ModelRenderer.hpp
        include/Core/Component/CircleCollider.hpp
        include/Core/Component/ITriggerStay.hpp
        include/Core/Component/IUpdate.hpp
        include/Core/Component/IStart.hpp
        include/Core/Component/ParticleBase.hpp
        include/Core/Component/IStartUI.hpp
        include/Core/SceneManager.hpp

        shaders/basic_f.glsl
        shaders/basic_v.glsl
        shaders/cubemap_f.glsl
        shaders/cubemap_v.glsl
        shaders/lights/ambiant_light_f.glsl
        shaders/lights/ambiant_light_v.glsl
        shaders/lights/directional_light_f.glsl
        shaders/lights/directional_light_v.glsl
        sources/Core/Graphics/Lights/AmbiantLight.cpp include/Core/Graphics/Lights/AmbiantLight.hpp include/Core/Graphics/Lights/DirectionalLight.hpp sources/Core/Graphics/Cubemap.cpp include/Core/Graphics/Cubemap.hpp)

add_executable(${NAME} ${SOURCES} ${HEADERS})

message("-- OpenGL --")
message("OpenGL librarie: " ${OPENGL_gl_LIBRARY})

message("-- GLM --")
message("glm includes: " ${GLM_INCLUDE_DIRS})

message("-- GLFW --")
message("GLFW librarie: " ${GLFW3_LIBRARY})
message("GLFW includes: " ${GLFW3_INCLUDE_DIR})

message("-- GLEW --")
message("GLEW librarie: " ${GLEW_LIBRARY})
message("GLEW includes: " ${GLEW_INCLUDE_DIR})

message("-- LibPNG --")
message("PNG librarie: " ${PNG_LIBRARY})

message("-- OpenAL --")
message("OpenAL librarie: " ${OPENAL_LIBRARY})
message("OpenAL include: " ${OPENAL_INCLUDE_DIR})

message("-- LibSndFile --")
message("LibSndFile librarie: " ${LIBSNDFILE_LIBRARIES})
message("LibSndFile include: " ${LIBSNDFILE_INCLUDE_DIRS})

message("-- Nlohmann Json --")
message("Nlohmann_json librarie: " nlohmann_json)

message("-- Assimp --")
message("Assimp librarie: " ${ASSIMP_LIBRARIES})
message("Assimp include: " ${ASSIMP_INCLUDE_DIRS})

message("-- Tiny obj loader --")
message("TinyObjLoader librarie: " ${TINYOBJLOADER_LIBRARY})
message("TinyObjLoader include: " ${TINYOBJLOADER_INCLUDE_DIR})

message("-- STB --")
message("STB include: " ${STB_INCLUDE_DIR})

message("-- JSON --")
message("JSON include: " ${JSON_INCLUDE_DIRS})

set(LIBRARIES
        ${OPENGL_gl_LIBRARY}
        ${GLFW3_LIBRARY}
        ${GLEW_LIBRARY}
        ${PNG_LIBRARY}
        ${OPENAL_LIBRARY}
        ${LIBSNDFILE_LIBRARIES}
        /usr/local/lib/libassimp.so
        ${TINYOBJLOADER_LIBRARY})

set(INCLUDES
        include/
        dependencies/nuklear/
        dependencies/
        ${GLM_INCLUDE_DIRS}
        ${GLFW3_INCLUDE_DIR}
        ${GLEW_INCLUDE_DIR}
        ${OPENAL_INCLUDE_DIR}
        ${LIBSNDFILE_INCLUDE_DIRS}
        ${ASSIMP_INCLUDE_DIRS}
        ${JSON_INCLUDE_DIRS}
        ${TINYOBJLOADER_INCLUDE_DIR}
        ${STB_INCLUDE_DIR})

target_link_libraries(${NAME} PUBLIC ${LIBRARIES})
target_include_directories(${NAME} PUBLIC ${INCLUDES})

file(COPY assets DESTINATION .)
file(COPY assets_boot DESTINATION .)
file(COPY models DESTINATION .)
file(COPY shaders DESTINATION .)
file(COPY Prefabs DESTINATION .)
file(COPY testSettings.json DESTINATION .)

add_custom_command(TARGET ${NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:${NAME}>/assets)
add_custom_command(TARGET ${NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/shaders $<TARGET_FILE_DIR:${NAME}>/shaders)
