#pragma once
#ifndef OPEN_CYCLE_TIME_GUI_CONTEXT_H
#define OPEN_CYCLE_TIME_GUI_CONTEXT_H
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <string>

namespace oct {
class GUIContext {
public:
    GUIContext(const std::string& window_title, unsigned short width,
               unsigned short height);
    ~GUIContext();
    void loop();
    bool isActive() const;

private:
    GLFWwindow* window;
    static GLFWwindow* initialiseGLFW(const std::string& window_title,
                                      unsigned short width,
                                      unsigned short height);
    static void errorCallbackGLFW(int error, const char* description);
};
} // namespace oct

#endif // OPEN_CYCLE_TIME_GUI_CONTEXT_H
