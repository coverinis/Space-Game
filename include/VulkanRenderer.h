#pragma once
#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <optional>

class VulkanRenderer {
public:
    VulkanRenderer();
    ~VulkanRenderer();

    void init(GLFWwindow* window);
    void draw();

private:
    VkInstance instance{};
    VkSurfaceKHR surface{};
    VkDevice device{};
    VkPhysicalDevice physicalDevice{};
    VkQueue graphicsQueue{};
    VkSwapchainKHR swapchain{};

    void createInstance();
    void pickPhysicalDevice();
    void createDevice();
    void createSurface(GLFWwindow* window);
};
