#include "VulkanRenderer.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <memory>

int main() {
    if (!glfwInit()) {
        std::cerr << "Failed to init GLFW" << std::endl;
        return -1;
    }
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    auto windowDeleter = [](GLFWwindow* w){ if (w) glfwDestroyWindow(w); };
    std::unique_ptr<GLFWwindow, decltype(windowDeleter)> window(
        glfwCreateWindow(800, 600, "Space Game Vulkan", nullptr, nullptr), windowDeleter);
    if (!window) {
        std::cerr << "Failed to create window" << std::endl;
        glfwTerminate();
        return -1;
    }

    VulkanRenderer renderer;
    try {
        renderer.init(window.get());
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        // window will be automatically destroyed when the unique_ptr goes out
        // of scope, so we just terminate GLFW here
        glfwTerminate();
        return -1;
    }

    while (!glfwWindowShouldClose(window.get())) {
        glfwPollEvents();
        renderer.draw();
    }

    glfwTerminate();
    return 0;
}
