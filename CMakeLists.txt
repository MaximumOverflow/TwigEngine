cmake_minimum_required(VERSION 3.13)
project(Twig_Engine)

set(CMAKE_CXX_STANDARD 17)

add_library(Twig_Engine src/include/TwigEngine.h src/Application.cpp src/include/Application.h src/include/Debug.h src/cpp/Video/Renderer.cpp src/include/Video/Renderer.h src/include/Video/Window.h src/cpp/Video/GL/GL_Window.cpp src/include/Video/GL/GL_Window.h src/include/Video/VK/VK_Window.h src/cpp/Video/VK/VK_Window.cpp src/include/Video/VertexArrayObject.h src/include/Video/VertexBufferObject.h src/cpp/Video/GL/GL_VertexArrayObject.cpp src/include/Video/GL/GL_VertexArrayObject.h src/cpp/Video/GL/GL_VertexBufferObject.cpp src/include/Video/GL/GL_VertexBufferObject.h src/include/Types.h)
add_compile_definitions(TE_PLATFORM_LINUX)


target_link_libraries(Twig_Engine GLFW)
add_compile_definitions(GLFW_INCLUDE_VULKAN)

target_link_libraries(Twig_Engine glew)

target_link_libraries(Twig_Engine OpenGL)

find_package(Vulkan)
target_link_libraries(Twig_Engine Vulkan::Vulkan)

find_package(glm)
target_link_libraries(Twig_Engine glm)

target_link_libraries(Twig_Engine spdlog)