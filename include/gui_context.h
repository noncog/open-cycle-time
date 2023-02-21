#pragma once
#ifndef OPEN_CYCLE_TIME_GUI_CONTEXT_H
#define OPEN_CYCLE_TIME_GUI_CONTEXT_H
#define GLFW_INCLUDE_NONE
#include "gui_functions.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <imgui.h>
#include <string>
#include <vector>

namespace oct {
class GUIContext {
public:
    GUIContext(const std::string& window_title, unsigned short width,
               unsigned short height);
    ~GUIContext();
    void loop();
    bool isActive() const;
    GLFWwindow* window;

private:
    const char* glsl_version = "#version 410";
    ImGuiIO& io;
    int display_w;
    int display_h;
    ImVec4 clear_color = ImVec4(0.29f, 0.29f, 0.38f, 0.4f);
    oct::GUIFunctions gui;
    static void errorCallbackGLFW(int error, const char* description);
    static GLFWwindow* initialiseGLFW(const std::string& window_title,
                                      unsigned short width,
                                      unsigned short height);
    ImGuiIO& initialiseIMGUI();
    void buildGUI();
    void renderGUI();
};
} // namespace oct

#endif // OPEN_CYCLE_TIME_GUI_CONTEXT_H
