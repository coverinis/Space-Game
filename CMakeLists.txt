cmake_minimum_required(VERSION 3.16)
project(SpaceGameVulkan)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Vulkan REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)

add_executable(space_game
    Space-Game/main.cpp
    Space-Game/VulkanRenderer.cpp
)

target_include_directories(space_game PRIVATE ${GLFW_INCLUDE_DIRS})
target_link_libraries(space_game PRIVATE Vulkan::Vulkan ${GLFW_LIBRARIES})
