cmake_minimum_required(VERSION 3.13)
project(Twig_Engine)

set(CMAKE_CXX_STANDARD 17)

add_library(Twig_Engine src/include/TwigEngine.h src/cpp/Application.cpp src/include/Application.h src/include/Debug.h src/cpp/Video/Renderer.cpp src/include/Video/Renderer.h src/include/Video/Window.h src/cpp/Video/GL/GL_Window.cpp src/include/Video/GL/GL_Window.h src/include/Video/VK/VK_Window.h src/cpp/Video/VK/VK_Window.cpp src/include/Video/VertexArrayObject.h src/include/Video/VertexBufferObject.h src/cpp/Video/GL/GL_VertexArrayObject.cpp src/include/Video/GL/GL_VertexArrayObject.h src/cpp/Video/GL/GL_VertexBufferObject.cpp src/include/Video/GL/GL_VertexBufferObject.h src/include/Types/Types.h src/cpp/Global.cpp src/include/Global.h src/include/TE_Macros.h src/include/Video/Shader.h src/cpp/Video/GL/GL_Shader.cpp src/include/Video/GL/GL_Shader.h src/include/Video/IndexBufferObject.h src/cpp/Video/GL/GL_IndexBufferObject.cpp src/include/Video/GL/GL_IndexBufferObject.h src/include/Events/Event.h src/include/Events/MouseEvents.h src/cpp/Events/MouseEvents.cpp src/include/Events/EventHandler.h src/cpp/Events/EventHandler.cpp src/cpp/Modules/Listeners/EventListener.cpp src/include/Modules/Listeners/EventListener.h src/cpp/Input.cpp src/include/Input.h src/include/Events/KeyboardEvents.h src/cpp/Events/KeyboardEvents.cpp src/include/Events/WindowEvents.h src/cpp/Events/WindowEvents.cpp src/include/Modules/Module.h src/include/Types/KeyCodes.h src/include/Types/MouseCodes.h src/cpp/Types/Types.cpp src/cpp/Layers/Layer.cpp src/include/Layers/Layer.h src/cpp/Layers/LayerStack.cpp src/include/Layers/LayerStack.h src/cpp/Objects/GameObjects/GameObject.cpp src/include/Objects/GameObjects/GameObject.h src/cpp/EntityManager.cpp src/include/EntityManager.h src/cpp/Layers/Overlay.cpp src/include/Layers/Overlay.h src/cpp/Video/VertexArrayObject.cpp src/cpp/Video/VertexBufferObject.cpp src/cpp/Video/IndexBufferObject.cpp src/cpp/Video/Shader.cpp src/cpp/Objects/Mesh.cpp src/include/Objects/Mesh.h src/cpp/Modules/MeshRenderer.cpp src/include/Modules/MeshRenderer.h src/cpp/Objects/GameObjects/Camera.cpp src/include/Objects/GameObjects/Camera.h src/cpp/Video/FrameBufferObject.cpp src/include/Video/FrameBufferObject.h src/cpp/Modules/Transform.cpp src/include/Modules/Transform.h src/cpp/Modules/Module.cpp src/cpp/Debug.cpp src/cpp/Time.cpp src/include/Time.h src/cpp/Video/GL/GL_FrameBufferObject.cpp src/include/Video/GL/GL_FrameBufferObject.h src/cpp/Objects/GameObjects/Light.cpp src/include/Objects/GameObjects/Light.h src/include/External/stb/stb_image.cpp src/cpp/Video/Texture.cpp src/include/Video/Texture.h src/cpp/Video/GL/GL_Texture.cpp src/include/Video/GL/GL_Texture.h src/include/Video/RenderingAPI.h src/cpp/Video/GL/API_OpenGL.cpp src/include/Video/GL/API_OpenGL.h src/cpp/Video/VK/API_Vulkan.cpp src/include/Video/VK/API_Vulkan.h src/cpp/Audio/AudioManager.cpp src/include/Audio/AudioManager.h src/include/Audio/AudioBuffer.cpp src/include/Audio/AudioBuffer.h src/cpp/ResourceManager.cpp src/include/ResourceManager.h src/include/Asset.h src/cpp/Video/InternalShaders/DefaultDiffuse.h src/cpp/Layers/RenderingLayer.cpp src/include/Layers/RenderingLayer.h src/cpp/Video/InternalShaders/DefaultFlat.h src/cpp/Layers/InputLayer.cpp src/include/Layers/InputLayer.h src/include/Modules/Listeners/InputListener.cpp src/include/Modules/Listeners/InputListener.h src/cpp/Layers/ApplicationEventLayer.cpp src/include/Layers/ApplicationEventLayer.h)
add_compile_definitions(TE_PLATFORM_LINUX)


target_link_libraries(Twig_Engine GLFW)
add_compile_definitions(GLFW_INCLUDE_VULKAN)

target_link_libraries(Twig_Engine glew)

target_link_libraries(Twig_Engine OpenGL)

find_package(Vulkan)
target_link_libraries(Twig_Engine Vulkan::Vulkan)

find_package(glm)
target_link_libraries(Twig_Engine glm)

find_package(OpenAL)
target_link_libraries(Twig_Engine openal)

include_directories(src/include/External src/include src/cpp/Video/InternalShaders/)