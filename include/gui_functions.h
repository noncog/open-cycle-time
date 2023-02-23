#pragma once
#ifndef OPEN_CYCLE_TIME_GUI_FUNCTIONS_H
#define OPEN_CYCLE_TIME_GUI_FUNCTIONS_H
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <imgui.h>
#include <opencv2/opencv.hpp>

namespace oct {
class GUIFunctions {
public:
    GUIFunctions(GLFWwindow* window);
    ~GUIFunctions();
    void mainGUI();

private:
    struct Algorithms;
    friend struct Algorithms;
    std::string file_name;
    int frame_rate;
    int first_frame;
    int last_frame;
    int max_frame;
    int current_frame;
    int prev_frame;
    float video_length;
    GLuint texture;
    cv::Mat frame;
    cv::Mat sub_image;
    std::vector<cv::Mat> frames;
    ImVec2 viewer_start_pos;
    ImVec2 viewer_size;
    ImVec2 selection_start_pos;
    ImVec2 selection_end_pos;
    ImVec2 viewport_center;
    int viewer_center_offset;
    bool selection;
    int viewer_width;  // to be replaced
    int viewer_height; // to be replaced
    GLFWwindow* window;
    // Dear ImGUI control variables
    // initialized here to remove repeat creation in main loop
    // Debug menu flags
    bool show_imgui_metrics;
    bool show_imgui_demo;
    bool show_implot_metrics;
    bool show_implot_demo;
    // Loading control
    bool show_main_window;
    bool use_work_area;
    // static bool show_splash = true;
    bool show_load_dialog;
    bool skip_load_file;
    bool show_load_error;
    bool skip_loader_check;
    bool skip_get_size;
    bool show_video_size;
    bool right_type;
    bool load_full;
    bool load_portion;
    bool ready_load_portion;
    bool show_viewer;
    bool disable_all;
    bool render_rect;
    bool click_in_rect;
    bool show_results;
    std::vector<float> results;
    std::vector<int> peak_indexes;
    int selected_algo;
    // Private functions
    bool typeCheck();
    void resetVariables();
    void showMenuBar();
    void loadFile();
    void showViewer();
    void runComparison(float (*values_getter)(void* data, int idx, cv::Mat* m,
                                              cv::Mat* c));
    void normalizeResults();
};
} // namespace oct

#endif // OPEN_CYCLE_TIME_GUI_FUNCTIONS_H
