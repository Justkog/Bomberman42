cmake_minimum_required(VERSION 3.5)

set(NAME Bomberman)

project(${NAME})

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

find_package(glm REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)
find_package(PNG REQUIRED)
find_package(OpenAL REQUIRED)
find_package(LibSndFile REQUIRED)
find_package(nlohmann_json REQUIRED)
find_package(assimp REQUIRED)

set(SOURCES
        sources/main.cpp

#        sources/sigslot/src/signal.cpp

        sources/Core/Window.cpp
        sources/Core/Time.cpp
        sources/Core/SceneManager.cpp
        sources/Core/Json/Json.cpp
        sources/Core/Json/JsonSerializable.cpp
        sources/Core/AScene.cpp
        sources/Core/GameObject.cpp
        sources/Core/Transform.cpp
        sources/Core/Input.cpp
        sources/Core/Camera.cpp
        sources/Core/Mathf.cpp

        sources/Core/Component/Component.cpp
        sources/Core/Component/MeshRenderer.cpp
        sources/Core/Component/RaysRenderer.cpp
        sources/Core/Component/ACollider.cpp
        sources/Core/Component/BoxCollider2D.cpp
        sources/Core/Component/CircleCollider.cpp
        sources/Core/Component/RigidBody2D.cpp
        sources/Core/Component/ParticleBase.cpp
        sources/Core/Component/ParticleExplode.cpp
        sources/Core/Component/ModelRenderer.cpp

        sources/Core/Graphics/Mesh.cpp
        sources/Core/Graphics/MeshBuilder.cpp
        sources/Core/Graphics/ShaderProgram.cpp
        sources/Core/Graphics/Graphics.cpp
        sources/Core/Graphics/AMaterial.cpp
        sources/Core/Graphics/Texture.cpp

        sources/Core/Physics/Physics.cpp

        sources/Core/IO/FileUtils.cpp

        sources/Core/Audio/AudioListener.cpp
        sources/Core/Audio/AudioSource.cpp
        sources/Core/Audio/AudioClip.cpp

        sources/Core/BeerRoutine/BeerRoutine.cpp
        sources/Core/BeerRoutine/ARoutineRunner.cpp

        sources/Game/Assets.cpp
        sources/Game/SceneTest.cpp
        sources/Game/Components/Character.cpp
        sources/Game/Components/MouseRayTest.cpp
        sources/Game/Components/Player.cpp
        sources/Game/Components/IA.cpp
        sources/Game/Components/CameraController.cpp
        sources/Game/Components/Settings.cpp
        sources/Game/Components/Item.cpp
        sources/Game/Components/Bomb.cpp
        sources/Game/Components/Map.cpp
        sources/Game/Components/Breakable.cpp
        sources/Game/Components/BeerRoutineTester.cpp
        sources/Game/CameraTest.cpp)

add_executable(${NAME} ${SOURCES})

find_package(glm REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)
find_package(PNG REQUIRED)
find_package(OpenAL REQUIRED)
find_package(LibSndFile REQUIRED)
find_package(nlohmann_json REQUIRED)
find_package(assimp REQUIRED)

message("glm includes: " ${GLM_INCLUDE_DIRS})
message("OpenGL librarie: " ${OPENGL_gl_LIBRARY})
message("GLFW librarie: " ${GLFW3_LIBRARY})
message("GLEW librarie: " ${GLEW_LIBRARY})
message("PNG librarie: " ${PNG_LIBRARY})
message("OpenAL librarie: " ${OpenAL_LIBRARY})

target_include_directories(${NAME} PUBLIC ${glm_INCLUDE_DIR})
