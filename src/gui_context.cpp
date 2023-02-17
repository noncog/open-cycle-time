#include "gui_context.h"
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <implot.h>
#include <iostream>
#include <tinyfiledialogs.h>

namespace oct {
GUIContext::GUIContext(const std::string& window_title, unsigned short width,
                       unsigned short height)
    : window{initialiseGLFW(window_title, width, height)}
    , io{GUIContext::initialiseIMGUI()}
    , display_w{0}
    , display_h{0}
    , file_name{""}
    , frame_rate{0}
    , first_frame{1}
    , last_frame{0}
    , max_frame{0}
    , video_length{0.0}
    , texture{static_cast<GLuint>(-1)}
    , texture_current{false}
    , viewer_width{0}
    , viewer_height{0}
    , current_frame{1}
    , prev_frame{0} {}
GUIContext::~GUIContext() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImPlot::DestroyContext();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();
}
void GUIContext::loop() {
    glfwPollEvents();
    buildGUI();
    renderGUI();
}
bool GUIContext::isActive() const {
    return !glfwWindowShouldClose(window);
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
bool GUIContext::typeCheck() {
    std::string ending_one = "mp4";
    std::string ending_two = "avi";
    std::string ending_three = "mov";
    if (file_name.length() >= ending_one.length()) {
        if (0
            == file_name.compare(file_name.length() - ending_one.length(),
                                 ending_one.length(), ending_one)) {
            return true;
        } else if (0
                   == file_name.compare(file_name.length()
                                            - ending_two.length(),
                                        ending_two.length(), ending_two)) {
            return true;
        } else if (0
                   == file_name.compare(file_name.length()
                                            - ending_three.length(),
                                        ending_three.length(), ending_three)) {
            return true;
        }
    }
    return false;
}
void GUIContext::errorCallbackGLFW(int error, const char* description) {
    std::cerr << "GLFW Error (" << error << ") " << description << std::endl;
}
ImGuiIO& GUIContext::initialiseIMGUI() {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImPlot::CreateContext();
    ImGuiIO& getIo = ImGui::GetIO();
    (void)getIo;
    getIo.ConfigFlags |=
        ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls

    // Setup Dear ImGUI style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    // TODO: Load Fonts
    // - If no fonts are loaded, dear imgui will use the default font. You can
    // also load multiple fonts and use ImGui::PushFont()/PopFont() to select
    // them.
    // - AddFontFromFileTTF() will return the ImFont* so you can store it if you
    // need to select the font among multiple.
    // - If the file cannot be loaded, the function will return NULL. Please
    // handle those errors in your application (e.g. use an assertion, or
    // display an error and quit).
    // - The fonts will be rasterized at a given size (w/ oversampling) and
    // stored into a texture when calling
    // ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame
    // below will call.
    // - Use '#define IMGUI_ENABLE_FREETYPE' in your imconfig file to use
    // Freetype for higher quality font rendering.
    // - Read 'docs/FONTS.md' for more instructions and details.
    // - Remember that in C/C++ if you want to include a backslash \ in a string
    // literal you need to write a double backslash \\ !
    // io.Fonts->AddFontDefault();
    // io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\segoeui.ttf", 18.0f);
    // io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
    // io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
    // io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
    // ImFont* font =
    // io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f,
    // NULL, io.Fonts->GetGlyphRangesJapanese()); IM_ASSERT(font != NULL);

    return getIo;
}
void GUIContext::buildGUI() {
    // Make a new frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // Build the main GUI

    // Debug menu flags
    static bool show_imgui_demo = false;
    static bool show_implot_demo = false;
    static bool show_implot_metrics = false;
    static bool show_imgui_metrics = false;

    // Debug menu actions
    if (show_imgui_demo) {
        ImGui::ShowDemoWindow(&show_imgui_demo);
    }
    if (show_implot_demo) {
        ImPlot::ShowDemoWindow(&show_implot_demo);
    }
    if (show_imgui_metrics) {
        ImGui::ShowMetricsWindow(&show_imgui_metrics);
    }
    if (show_implot_metrics) {
        ImPlot::ShowMetricsWindow(&show_implot_metrics);
    }

    // loader variables
    static bool show_load_dialog = false;
    static bool skip_load_file = false;
    static bool show_load_error = false;
    static bool skip_loader_check = false;
    static bool skip_get_size = false;
    static bool show_video_size = false;
    static bool right_type = false;
    static bool load_full = false;
    static bool load_portion = false;
    static bool ready_load_portion = false;
    static bool show_frame = false;
    static bool disable_all = true;

    // Main menu bar
    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("File")) {
            if (ImGui::MenuItem("Open", nullptr)) {
                // reset all loader variables when loading a new video
                show_load_dialog = false;
                skip_load_file = false;
                show_load_error = false;
                skip_loader_check = false;
                skip_get_size = false;
                show_video_size = false;
                right_type = false;
                load_full = false;
                load_portion = false;
                ready_load_portion = false;
                show_frame = false;
                disable_all = true;
                file_name = "";
                frames.clear();
                frame_rate = 0;
                first_frame = 1;
                last_frame = 0;
                max_frame = 0;
                video_length = 0.0;
                texture_current = false;
                viewer_width = 0;
                viewer_height = 0;
                current_frame = 1;
                prev_frame = 0;

                char const* lTheOpenFileName;
                char const* lFilterPatterns[3] = {"*.mp4", "*.avi", "*.mov"};
                lTheOpenFileName =
                    tinyfd_openFileDialog("Select a Video File", "", 3,
                                          lFilterPatterns, "Video files", 0);
                if (!lTheOpenFileName) {
                    tinyfd_messageBox("Error", "File name is empty.", "ok",
                                      "error", 0);
                } else {
                    file_name = lTheOpenFileName;
                    if (typeCheck()) {
                        right_type = true;
                    }
                    show_load_dialog = true;
                }
            }
            if (ImGui::MenuItem("Quit", nullptr)) {
                glfwSetWindowShouldClose(window, 1);
            }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Debug")) {
            if (ImGui::MenuItem("Show ImGUI Demo", nullptr, &show_imgui_demo)) {
            }
            if (ImGui::MenuItem("Show ImPlot Demo", nullptr,
                                &show_implot_demo)) {
            }
            if (ImGui::MenuItem("Show ImGUI Metrics", nullptr,
                                &show_imgui_metrics)) {
            }
            if (ImGui::MenuItem("Show ImPlot Metrics", nullptr,
                                &show_implot_metrics)) {
            }
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }

    // Main Window
    static bool show_main_window = true;
    static bool use_work_area = true;
    // static bool show_splash = true;

    static ImGuiWindowFlags flags =
        ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground
        | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize
        | ImGuiWindowFlags_NoSavedSettings;
    const ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(use_work_area ? viewport->WorkPos : viewport->Pos);
    ImGui::SetNextWindowSize(use_work_area ? viewport->WorkSize
                                           : viewport->Size);

    ImGui::Begin("Main Window", &show_main_window, flags);
    ImVec2 center = ImGui::GetMainViewport()->GetCenter();
    if (show_load_dialog) {
        if (show_load_error) {
            ImGui::OpenPopup("Error:");
            ImGui::SetNextWindowPos(center, ImGuiCond_Appearing,
                                    ImVec2(0.5f, 0.5f));
            if (ImGui::BeginPopupModal("Error:", NULL,
                                       ImGuiWindowFlags_AlwaysAutoResize)) {
                ImGui::Text("The selected file cannot be opened.");
                ImGui::Separator();
                // ImGui::PopStyleVar();
                if (ImGui::Button("OK", ImVec2(120, 0))) {
                    ImGui::CloseCurrentPopup();
                    show_load_dialog = false;
                }
                ImGui::EndPopup();
            }
        }
        if (!skip_load_file) {
            cv::VideoCapture frame_loader(file_name);
            if (right_type && frame_loader.isOpened()) {
                if (!skip_get_size) {
                    frame_rate = frame_loader.get(cv::CAP_PROP_FPS);
                    while (true) {
                        frame_loader >> frame;
                        if (frame.empty()) {
                            break;
                        }
                        last_frame++;
                    }
                    max_frame = last_frame;
                    skip_get_size = true;
                    show_video_size = true;
                }
                if (show_video_size) {
                    ImGui::OpenPopup("Video File Info:");
                    ImGui::SetNextWindowPos(center, ImGuiCond_Appearing,
                                            ImVec2(0.5f, 0.5f));
                    if (ImGui::BeginPopupModal(
                            "Video File Info:", NULL,
                            ImGuiWindowFlags_AlwaysAutoResize)) {
                        video_length = last_frame / frame_rate;
                        ImGui::Text(
                            "The selected file contains %d frames and is "
                            "%.02f seconds long.\n\nDo you want to load "
                            "the "
                            "entire file or just a portion?",
                            last_frame, video_length);
                        ImGui::Separator();
                        if (ImGui::Button("Load Portion", ImVec2(120, 0))) {
                            show_video_size = false;
                            load_portion = true;
                            ImGui::CloseCurrentPopup();
                        }
                        ImGui::SameLine();
                        if (ImGui::Button("Load All", ImVec2(120, 0))) {
                            show_video_size = false;
                            load_full = true;
                            ImGui::CloseCurrentPopup();
                        }
                        ImGui::EndPopup();
                    }
                }
                if (load_full) {
                    last_frame = 0;
                    while (true) {
                        frame_loader >> frame;
                        if (frame.empty()) {
                            break;
                        }
                        frames.push_back(frame);
                        frame.release();
                        last_frame++;
                    }
                    load_full = false;
                    show_frame = true;
                    disable_all = false;
                }
                if (load_portion) {
                    ImGui::OpenPopup("Select Frames:");
                    ImGui::SetNextWindowPos(center, ImGuiCond_Appearing,
                                            ImVec2(0.5f, 0.5f));
                    if (ImGui::BeginPopupModal(
                            "Select Frames:", NULL,
                            ImGuiWindowFlags_AlwaysAutoResize)) {
                        float selection_length =
                            (last_frame - first_frame) / frame_rate;
                        ImGui::DragIntRange2("", &first_frame, &last_frame, 1,
                                             1, max_frame, "Start: %d",
                                             "End: %d");
                        if (ImGui::Button("Load", ImVec2(120, 0))) {
                            ready_load_portion = true;
                            ImGui::CloseCurrentPopup();
                        }
                        ImGui::SameLine();
                        ImGui::Text("%.02f secs", selection_length);
                        ImGui::EndPopup();
                    }
                    if (ready_load_portion) {
                        for (int i = 1; i <= last_frame; i++) {
                            if (i < first_frame) {
                                continue;
                            }
                            frame_loader >> frame;
                            if (frame.empty()) {
                                break;
                            }
                            frames.push_back(frame);
                            frame.release();
                        }
                        load_portion = false;
                        show_frame = true;
                        disable_all = false;
                    }
                }
            } else {
                show_load_error = true;
                skip_load_file = true;
            }
        }
    }
    ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_None;
    if (ImGui::BeginTabBar("Main Tab Bar", tab_bar_flags)) {
        if (ImGui::BeginTabItem("Generator")) {
            ImGui::BeginChild("Viewer Window",
                              ImVec2(0.0f, viewport->Size.y - 200));
            if (show_frame) {
                // If we don't have a texture, make it, otherwise just show it.
                if (texture_current == false) {
                    glGenTextures(1, &texture);
                    glBindTexture(GL_TEXTURE_2D, texture);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                                    GL_LINEAR);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
                                    GL_LINEAR);
                    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                                 frames[current_frame].cols,
                                 frames[current_frame].rows, 0, GL_RGB,
                                 GL_UNSIGNED_BYTE, frames[current_frame].data);
                    texture_current = true;
                    prev_frame = current_frame;
                }

                if (current_frame != prev_frame) {
                    texture_current = false;
                }

                ImVec2 window_start = ImGui::GetCursorScreenPos();
                ImVec2 window_region = ImGui::GetContentRegionAvail();
                ImVec2 window_max = ImVec2(window_region.x + window_start.x,
                                           window_region.y + window_start.y);

                // Find a max frame viewer size that honors video aspect ratio
                if (viewer_width == 0 || viewer_height == 0) {
                    int frame_width = frames[current_frame].cols;
                    int frame_height = frames[current_frame].rows;
                    float aspect_ratio =
                        (float)frame_width / (float)frame_height;
                    int minimum_width = 426;  // This is 240p video width.
                    int minimum_height = 240; // This is 240p video height.

                    if (frame_width > frame_height) {
                        for (int i = minimum_width; i <= window_max.x; i++) {
                            float result = i / aspect_ratio;
                            if (result <= window_max.y
                                && result == static_cast<int>(result)) {
                                viewer_width = i;
                                viewer_height = result;
                            }
                        }
                    } else {
                        for (int i = minimum_height; i <= window_max.y; i++) {
                            float result = i * aspect_ratio;
                            if (result <= window_max.x
                                && result == static_cast<int>(result)) {
                                viewer_height = i;
                                viewer_width = result;
                            }
                        }
                    }
                }
                int center_diff = (window_max.x - viewer_width) / 2;
                ImGui::GetWindowDrawList()->AddImage(
                    (void*)(intptr_t)texture,
                    ImVec2((window_start.x + center_diff), window_start.y),
                    ImVec2((viewer_width + center_diff), viewer_height),
                    ImVec2(0, 0), ImVec2(1, 1));
            }
            ImGui::EndChild();
            ImGui::Separator();
            ImGui::BeginChild("Filler Window 1",
                              ImVec2(viewport->Size.x / 3, 0.0f));
            ImGui::EndChild();
            ImGui::SameLine();
            ImGui::BeginChild("Controls Window",
                              ImVec2(viewport->Size.x / 3, 0.0f));
            if (disable_all) {
                ImGui::BeginDisabled();
            }
            ImGui::SetNextItemWidth(viewport->Size.x / 3);
            ImGui::SliderInt("##", &current_frame, 1, max_frame, "%d",
                             ImGuiSliderFlags_None);
            if (disable_all) {
                ImGui::EndDisabled();
            }
            ImGui::EndChild();
            ImGui::SameLine();
            ImGui::BeginChild("Filler Window 2",
                              ImVec2(viewport->Size.x / 3, 0.0f));
            ImGui::EndChild();
            ImGui::EndTabItem();
        }
        ImGui::EndTabBar();
    }
    ImGui::End();
}
void GUIContext::renderGUI() {
    ImGui::Render();

    glfwGetFramebufferSize(window, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w,
                 clear_color.z * clear_color.w, clear_color.w);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(window);
}
} // namespace oct
