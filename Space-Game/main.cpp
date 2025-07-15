#include "VulkanRenderer.h"
#include <GLFW/glfw3.h>
#include <iostream>

int main() {
    if (!glfwInit()) {
        std::cerr << "Failed to init GLFW" << std::endl;
        return -1;
    }
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    GLFWwindow* window = glfwCreateWindow(800, 600, "Space Game Vulkan", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create window" << std::endl;
        glfwTerminate();
        return -1;
    }

    VulkanRenderer renderer;
    try {
        renderer.init(window);
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        renderer.draw();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
