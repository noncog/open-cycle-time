#pragma once
#ifndef OPEN_CYCLE_TIME_GUI_CONTEXT_H
#define OPEN_CYCLE_TIME_GUI_CONTEXT_H
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <imgui.h>
#include <opencv2/opencv.hpp>
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

private:
    const char* glsl_version = "#version 410";
    GLFWwindow* window;
    ImGuiIO& io;
    int display_w;
    int display_h;
    ImVec4 clear_color = ImVec4(0.29f, 0.29f, 0.38f, 0.4f);
    std::string file_name;
    bool typeCheck();
    cv::Mat frame;
    std::vector<cv::Mat> frames;
    int frame_rate;
    int first_frame;
    int last_frame;
    int max_frame;
    float video_length;
    GLuint texture;
    bool texture_current;
    int viewer_width;
    int viewer_height;
    int current_frame;
    int prev_frame;
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
