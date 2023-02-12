#include "gui_context.h"
#include <iostream>

namespace oct {
GUIContext::GUIContext(const std::string& window_title, unsigned short width,
                       unsigned short height)
    : window{initialiseGLFW(window_title, width, height)} {}
GUIContext::~GUIContext() {
    glfwTerminate();
}
void GUIContext::loop() {
    glfwSwapBuffers(window);
    glfwPollEvents();
}
bool GUIContext::isActive() const {
    return glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS
           && !glfwWindowShouldClose(window);
    // return !glfwWindowShouldClose(window);
}
GLFWwindow* GUIContext::initialiseGLFW(const std::string& window_title,
                                       unsigned short width,
                                       unsigned short height) {
    glfwSetErrorCallback(GUIContext::errorCallbackGLFW);

    // Initialise GLFW
    if (!glfwInit()) {
        throw std::runtime_error("Failed to initialise GLFW");
    }

    // Set GLFW window hints
    // GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    // const GLFWvidmode* mode = glfwGetVideoMode(monitor);
    // glfwWindowHint(GLFW_RED_BITS, mode->redBits);
    // glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
    // glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
    // glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
    glfwWindowHint(GLFW_SAMPLES, 2); // TODO: Check anti-aliasing value/need
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    // glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    // Create window with graphics context
    GLFWwindow* window =
        glfwCreateWindow(width, height, window_title.c_str(), nullptr, nullptr);

    if (!window) {
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        throw std::runtime_error("Failed to initialize GLAD");
    }

    // Enable vsync
    glfwSwapInterval(1);

    return window;
}
void GUIContext::errorCallbackGLFW(int error, const char* description) {
    std::cerr << "GLFW Error (" << error << ") " << description << std::endl;
}
} // namespace oct