#include "gui_functions.h"
#include <fstream>
#include <implot.h>
#include <math.h>
#include <tinyfiledialogs.h>

namespace oct {
GUIFunctions::GUIFunctions(GLFWwindow* window)
    : file_name("")
    , save_file("")
    , frame_rate(0)
    , first_frame(1)
    , last_frame(0)
    , max_frame(0)
    , current_frame(1)
    , prev_frame(0)
    , compare_start(0)
    , video_length(0.0)
    , texture(static_cast<GLuint>(-1))
    // frame
    // sub_image
    // frames
    // viewer_start_pos
    // viewer_size
    // selection_start_pos
    // selection_end_pos
    // viewport_center
    , viewer_center_offset(0)
    , viewer_width(0)  // TODO: to be replaced
    , viewer_height(0) // TODO: to be replaced
    , selection(false)
    , window(window)
    , show_imgui_metrics(false)
    , show_imgui_demo(false)
    , show_implot_metrics(false)
    , show_implot_demo(false)
    , show_main_window(true)
    , use_work_area(true)
    , show_load_dialog(false)
    , skip_load_file(false)
    , show_load_error(false)
    , skip_loader_check(false)
    , skip_get_size(false)
    , show_video_size(false)
    , right_type(false)
    , load_full(false)
    , load_portion(false)
    , ready_load_portion(false)
    , show_viewer(false)
    , disable_all(true)
    , render_rect(false)
    , click_in_rect(false)
    , show_results(false)
    , selection_warn(false)
    , selected_algo(0)
    , cycle_mean(0)
    , cycle_var(0)
    , cycle_stdev(0)
    , hard_reset(false) {}
GUIFunctions::~GUIFunctions() {}
struct GUIFunctions::Algorithms {
    static float Correlation(void*, int i, cv::Mat* m, cv::Mat* c) {
        // TODO: put elsewhere eventually
        int h_bins = 50, s_bins = 60;
        int histSize[] = {h_bins, s_bins};

        // These can stay the same but may want variable bins
        // hue varies from 0 to 179, saturation from 0 to 255
        float h_ranges[] = {0, 180};
        float s_ranges[] = {0, 256};
        const float* ranges[] = {h_ranges, s_ranges};
        // Use the 0-th and 1-st channels
        int channels[] = {0, 1};

        cv::Mat hist_sub;
        cv::Mat hist_compare;

        // find histogram of sub image
        calcHist(m, 1, channels, cv::Mat(), hist_sub, 2, histSize, ranges, true,
                 false);
        normalize(hist_sub, hist_sub, 0, 1, cv::NORM_MINMAX, -1, cv::Mat());
        // find histogram of compare image
        calcHist(c, 1, channels, cv::Mat(), hist_compare, 2, histSize, ranges,
                 true, false);
        normalize(hist_compare, hist_compare, 0, 1, cv::NORM_MINMAX, -1,
                  cv::Mat());

        // 4 separate compare methods 0-3 or 4 idk
        float comparison =
            compareHist(hist_sub, hist_compare, cv::HISTCMP_CORREL);

        return comparison;
    }
    static float Intersection(void*, int i, cv::Mat* m, cv::Mat* c) {
        // TODO: put elsewhere eventually
        int h_bins = 50, s_bins = 60;
        int histSize[] = {h_bins, s_bins};

        // These can stay the same but may want variable bins
        // hue varies from 0 to 179, saturation from 0 to 255
        float h_ranges[] = {0, 180};
        float s_ranges[] = {0, 256};
        const float* ranges[] = {h_ranges, s_ranges};
        // Use the 0-th and 1-st channels
        int channels[] = {0, 1};

        cv::Mat hist_sub;
        cv::Mat hist_compare;

        // find histogram of sub image
        calcHist(m, 1, channels, cv::Mat(), hist_sub, 2, histSize, ranges, true,
                 false);
        normalize(hist_sub, hist_sub, 0, 1, cv::NORM_MINMAX, -1, cv::Mat());
        // find histogram of compare image
        calcHist(c, 1, channels, cv::Mat(), hist_compare, 2, histSize, ranges,
                 true, false);
        normalize(hist_compare, hist_compare, 0, 1, cv::NORM_MINMAX, -1,
                  cv::Mat());

        // 4 separate compare methods 0-3 or 4 idk
        float comparison =
            compareHist(hist_sub, hist_compare, cv::HISTCMP_INTERSECT);

        return comparison;
    }
    static float Chisquare(void*, int i, cv::Mat* m, cv::Mat* c) {
        // TODO: put elsewhere eventually
        int h_bins = 50, s_bins = 60;
        int histSize[] = {h_bins, s_bins};

        // These can stay the same but may want variable bins
        // hue varies from 0 to 179, saturation from 0 to 255
        float h_ranges[] = {0, 180};
        float s_ranges[] = {0, 256};
        const float* ranges[] = {h_ranges, s_ranges};
        // Use the 0-th and 1-st channels
        int channels[] = {0, 1};

        cv::Mat hist_sub;
        cv::Mat hist_compare;

        // find histogram of sub image
        calcHist(m, 1, channels, cv::Mat(), hist_sub, 2, histSize, ranges, true,
                 false);
        normalize(hist_sub, hist_sub, 0, 1, cv::NORM_MINMAX, -1, cv::Mat());
        // find histogram of compare image
        calcHist(c, 1, channels, cv::Mat(), hist_compare, 2, histSize, ranges,
                 true, false);
        normalize(hist_compare, hist_compare, 0, 1, cv::NORM_MINMAX, -1,
                  cv::Mat());

        // 4 separate compare methods 0-3 or 4 idk
        float comparison =
            compareHist(hist_sub, hist_compare, cv::HISTCMP_CHISQR);

        return comparison;
    }
    static float Bhattacharyya(void*, int i, cv::Mat* m, cv::Mat* c) {
        // TODO: put elsewhere eventually
        int h_bins = 50, s_bins = 60;
        int histSize[] = {h_bins, s_bins};

        // These can stay the same but may want variable bins
        // hue varies from 0 to 179, saturation from 0 to 255
        float h_ranges[] = {0, 180};
        float s_ranges[] = {0, 256};
        const float* ranges[] = {h_ranges, s_ranges};
        // Use the 0-th and 1-st channels
        int channels[] = {0, 1};

        cv::Mat hist_sub;
        cv::Mat hist_compare;

        // find histogram of sub image
        calcHist(m, 1, channels, cv::Mat(), hist_sub, 2, histSize, ranges, true,
                 false);
        normalize(hist_sub, hist_sub, 0, 1, cv::NORM_MINMAX, -1, cv::Mat());
        // find histogram of compare image
        calcHist(c, 1, channels, cv::Mat(), hist_compare, 2, histSize, ranges,
                 true, false);
        normalize(hist_compare, hist_compare, 0, 1, cv::NORM_MINMAX, -1,
                  cv::Mat());

        // 4 separate compare methods 0-3 or 4 idk
        float comparison =
            compareHist(hist_sub, hist_compare, cv::HISTCMP_BHATTACHARYYA);

        return comparison;
    }
};
void GUIFunctions::mainGUI() {

    // Main menu bar
    showMenuBar();

    // Set window flags
    static ImGuiWindowFlags flags =
        ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground
        | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize
        | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoNav
        | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoScrollbar;

    // Limit main window to below menu bar
    const ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(use_work_area ? viewport->WorkPos : viewport->Pos);
    ImGui::SetNextWindowSize(use_work_area ? viewport->WorkSize
                                           : viewport->Size);
    // Create window
    ImGui::Begin("Main Window", &show_main_window, flags);

    // Keep a reference to center of this window
    viewport_center = ImGui::GetMainViewport()->GetCenter();

    // Check if should load a file
    loadFile();

    selectionWarn();

    // Create tabs layout for the main windows: generator and its output
    ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_None;
    if (ImGui::BeginTabBar("Main Tab Bar", tab_bar_flags)) {
        if (ImGui::BeginTabItem("Generator")) {

            // Create child window for the video viewer
            ImGui::BeginChild("Viewer Window",
                              ImVec2(0.0f, viewport->Size.y - 200));

            // Show the video viewer and controls after video is loaded
            showViewer();
            ImGui::EndChild();
            ImGui::Separator();
            // Show the controls
            ImGui::BeginChild("Filler Window 1",
                              ImVec2(viewport->Size.x / 4, 0.0f));
            ImGui::EndChild();
            ImGui::SameLine();
            ImGui::BeginChild("Controls Window",
                              ImVec2(viewport->Size.x / 2, 0.0f));
            if (disable_all) {
                ImGui::BeginDisabled();
            }
            ImGui::SetNextItemWidth(viewport->Size.x / 2);
            ImGui::SliderInt("##", &current_frame, 1, max_frame, "%d",
                             ImGuiSliderFlags_None);

            // center buttons
            ImGuiStyle& style = ImGui::GetStyle();
            float size = 41.0f;
            float avail = ImGui::GetContentRegionAvail().x;
            float offset = (avail - size) * 0.5f;
            if (offset > 0.0f) {
                ImGui::SetCursorPosX(ImGui::GetCursorPosX() + offset);
            }

            float spacing = ImGui::GetStyle().ItemInnerSpacing.x;
            ImGui::PushButtonRepeat(true);
            if (ImGui::ArrowButton("##left", ImGuiDir_Left)) {
                current_frame--;
            }
            ImGui::SameLine(0.0f, spacing);
            if (ImGui::ArrowButton("##right", ImGuiDir_Right)) {
                current_frame++;
            }
            ImGui::PopButtonRepeat();
            ImGui::Separator();
            // GetItemRectSize()

            static int func_type = 0;
            ImGui::SetNextItemWidth(ImGui::GetFontSize() * 10);
            ImGui::Combo(
                "Algorithm", &func_type,
                "Correlation\0Intersection\0Chi-square\0Bhattacharyya\0");
            float (*func)(void*, int, cv::Mat*, cv::Mat*) =
                (func_type == 0)   ? Algorithms::Correlation
                : (func_type == 1) ? Algorithms::Intersection
                : (func_type == 2) ? Algorithms::Chisquare
                                   : Algorithms::Bhattacharyya;
            selected_algo = func_type;

            // center the next button
            size =
                ImGui::CalcTextSize("Generate").x + style.FramePadding.x * 2.0f;
            avail = ImGui::GetContentRegionAvail().x;
            offset = (avail - size) * 0.5f;
            if (offset > 0.0f) {
                ImGui::SetCursorPosX(ImGui::GetCursorPosX() + offset);
            }
            // generate button
            if (ImGui::Button("Generate")) {
                if (selection_start_pos.x
                        == viewer_start_pos.x + viewer_center_offset
                    && selection_start_pos.y == viewer_start_pos.y
                    && selection_end_pos.x
                           == viewer_start_pos.x + viewer_center_offset
                                  + viewer_width
                    && selection_end_pos.y
                           == viewer_start_pos.y + viewer_height) {
                    selection_warn = true;
                } else {
                    resetVariables();
                    compare_start = current_frame;
                    runComparison(func);
                }
            }
            if (disable_all) {
                ImGui::EndDisabled();
            }
            ImGui::EndChild();
            ImGui::SameLine();
            ImGui::BeginChild("Filler Window 2",
                              ImVec2(viewport->Size.x / 4, 0.0f));
            ImGui::EndChild();
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Results", &show_results)) {
            ImGui::SetNextItemWidth(ImGui::GetFontSize() * 10);
            ImGui::LabelText("##label", "Correlation Data");
            ImGui::SameLine();
            static int corr_graph = 0;
            ImGui::RadioButton("Histogram", &corr_graph, 0);
            ImGui::SameLine();
            ImGui::RadioButton("Line Plot", &corr_graph, 1);
            ImGui::Separator();
            if (corr_graph == 0) {
                static ImPlotHistogramFlags
                    hist_flags; //= ImPlotHistogramFlags_Density;
                static int bins = 50;
                static double mu = 5;    // TODO: Remove
                static double sigma = 2; // TODO: Remove
                ImGui::SetNextItemWidth(200);
                if (ImGui::RadioButton("Sqrt", bins == ImPlotBin_Sqrt)) {
                    bins = ImPlotBin_Sqrt;
                }
                ImGui::SameLine();
                if (ImGui::RadioButton("Sturges", bins == ImPlotBin_Sturges)) {
                    bins = ImPlotBin_Sturges;
                }
                ImGui::SameLine();
                if (ImGui::RadioButton("Rice", bins == ImPlotBin_Rice)) {
                    bins = ImPlotBin_Rice;
                }
                ImGui::SameLine();
                if (ImGui::RadioButton("Scott", bins == ImPlotBin_Scott)) {
                    bins = ImPlotBin_Scott;
                }
                ImGui::SameLine();
                if (ImGui::RadioButton("N Bins", bins >= 0)) {
                    bins = 50;
                }
                if (bins >= 0) {
                    ImGui::SameLine();
                    ImGui::SetNextItemWidth(200);
                    ImGui::SliderInt("##Bins", &bins, 1, 100);
                }
                ImGui::SameLine();

                static bool range = false;
                ImGui::Checkbox("Range", &range);
                static ImVec2 new_range(
                    *min_element(results.begin(), results.end()),
                    *max_element(results.begin(), results.end()));
                if (range) {
                    ImGui::SameLine();
                    ImGui::SetNextItemWidth(200);
                    ImGui::DragFloat2(
                        "##Range", (float*)&new_range, 0.001f,
                        *min_element(results.begin(), results.end()),
                        *max_element(results.begin(), results.end()));
                }
                if (ImPlot::BeginPlot("##Histograms")) {
                    ImPlot::SetupAxes(NULL, NULL, ImPlotAxisFlags_AutoFit,
                                      ImPlotAxisFlags_AutoFit);
                    ImPlot::SetNextFillStyle(IMPLOT_AUTO_COL, 0.5f);
                    ImPlot::PlotHistogram(
                        "Empirical", results.data(), results.size(), bins, 1.0,
                        range ? ImPlotRange(new_range.x, new_range.y)
                              : ImPlotRange(),
                        hist_flags);
                    ImPlot::EndPlot();
                }
            } else {
                if (ImPlot::BeginPlot("Line Plots")) {
                    ImPlot::SetupAxes("Frame", "Correlation", 0,
                                      ImPlotAxisFlags_AutoFit
                                          | ImPlotAxisFlags_RangeFit);
                    ImPlot::SetupAxesLimits(
                        0, results.size(), 0,
                        *max_element(results.begin(), results.end()));
                    ImPlot::SetupAxisLimitsConstraints(ImAxis_X1, 0,
                                                       results.size());
                    ImPlot::PlotLine("Correlation", results.data(),
                                     results.size());
                    ImPlot::SetNextMarkerStyle(ImPlotMarker_Circle);
                    ImPlot::PlotInfLines("Matches Frames", peak_indexes.data(),
                                         peak_indexes.size());
                    ImPlot::EndPlot();
                }
            }
            ImGui::BeginChild("Filler Window 1",
                              ImVec2(viewport->Size.x / 6, 0.0f));
            ImGui::EndChild();
            ImGui::SameLine();
            ImGui::BeginChild("Information Window",
                              ImVec2(viewport->Size.x / 6, 0.0f));

            ImGui::LabelText("##label", "Information");
            ImGui::BulletText(
                "File: %s",
                file_name.substr(file_name.find_last_of("/\\") + 1).c_str());
            ImGui::BulletText("Frames Loaded: %d", max_frame - first_frame);
            ImGui::BulletText("Length: %.02f seconds", video_length);
            ImGui::BulletText("Frame Rate: %.02f", frame_rate);
            ImGui::BulletText("Frames Compared: %d",
                              last_frame - compare_start);
            ImGui::BulletText("Frames Matched: %d", (int)peak_indexes.size());
            ImGui::BulletText("Compare Start: %d", compare_start);
            ImGui::BulletText("Compare End: %d", last_frame);
            ImGui::Separator();
            ImGui::LabelText("##label", "Export");
            static bool check = false; // TODO: Consider refactor
            ImGui::Checkbox("Export data?", &check);
            if (!check) {
                ImGui::BeginDisabled();
            }
            const char* items[] = {"Correlation Data", "Raw Cycle Times",
                                   "Cycle Times", "Frame Matches"};
            static int item_current = 0;
            ImGuiStyle& style = ImGui::GetStyle();
            float size =
                ImGui::CalcTextSize("Export").x + style.FramePadding.x * 4;
            float avail = ImGui::GetContentRegionAvail().x;
            ImGui::SetNextItemWidth(avail - size);
            ImGui::Combo("##select-data", &item_current, items,
                         IM_ARRAYSIZE(items));

            // generate button
            ImGui::SameLine();
            if (ImGui::Button("Export")) {
                // std::cout << "save file: " << save_file << std::endl;
                std::ofstream saveStream;
                switch (item_current) {
                    case 0:
                        saveFile("/correlation.csv");
                        // std::cout << save_file << std::endl;
                        saveStream.open(save_file);
                        // send the column name
                        saveStream << "Correlations"
                                   << "\n";

                        // send data to the stream
                        for (int i = 0; i < results.size(); ++i) {
                            saveStream << results.at(i) << "\n";
                        }
                        break;
                    case 1:
                        saveFile("/raw_cycle_times.csv");
                        // std::cout << save_file << std::endl;
                        saveStream.open(save_file);
                        // send the column name
                        saveStream << "Raw Cycle Times"
                                   << "\n";

                        // send data to the stream
                        for (int i = 0; i < peak_indexes.size(); ++i) {
                            saveStream << peak_indexes.at(i) / frame_rate
                                       << "\n";
                        }
                        break;
                    case 2:
                        saveFile("/cycle_times.csv");
                        // std::cout << save_file << std::endl;
                        saveStream.open(save_file);
                        // send the column name
                        saveStream << "Cycle Times"
                                   << "\n";

                        // send data to the stream
                        for (int i = 0; i < cycle_times.size(); ++i) {
                            saveStream << cycle_times.at(i) << "\n";
                        }
                        break;
                    case 3:
                        saveFile("/frame_matches.csv");
                        // std::cout << save_file << std::endl;
                        saveStream.open(save_file);
                        // send the column name
                        saveStream << "Frame Matches"
                                   << "\n";

                        // send data to the stream
                        for (int i = 0; i < peak_indexes.size(); ++i) {
                            saveStream << peak_indexes.at(i) << "\n";
                        }

                        break;
                }
                // close the file stream
                saveStream.close();
            }
            if (!check) {
                ImGui::EndDisabled();
            }
            ImGui::EndChild();
            ImGui::SameLine();
            ImGui::BeginChild("Cycle Times Window",
                              ImVec2(viewport->Size.x / 3, 0.0f));
            ImGui::LabelText("##label", "Cycle Times");
            static int bins = ImPlotBin_Sqrt;
            ImVec2 window_max = ImGui::GetContentRegionAvail();
            if (ImPlot::BeginPlot("##Histograms",
                                  ImVec2(window_max.x, window_max.y * 0.75))) {
                ImPlot::SetupAxes(NULL, NULL, ImPlotAxisFlags_AutoFit,
                                  ImPlotAxisFlags_AutoFit);
                ImPlot::SetNextFillStyle(IMPLOT_AUTO_COL, 0.5f);
                ImPlot::PlotHistogram("Cycle Times", cycle_times.data(),
                                      cycle_times.size(), bins, 1.0,
                                      ImPlotRange());
                ImPlot::EndPlot();
                ImGui::BulletText("Cycle Count: %d",
                                  (int)peak_indexes.size() - 1);
                ImGui::BulletText("Cycle Mean: %.04f seconds", cycle_mean);
                ImGui::BulletText("Cycle Variance: %.05f seconds", cycle_var);
                ImGui::BulletText("Cycle Standard Deviation: %.05f seconds",
                                  cycle_stdev);
            }
            ImGui::EndChild();
            ImGui::SameLine();

            window_max = ImGui::GetContentRegionAvail();
            ImGui::BeginChild("Data Explorer Window",
                              ImVec2(viewport->Size.x / 6, 0.0f));
            // ImGui::LabelText("##label", "Data Explorer");
            ImGui::EndChild();
            ImGui::SameLine();
            ImGui::BeginChild("Filler Window 2",
                              ImVec2(viewport->Size.x / 6, 0.0f));
            ImGui::EndChild();
            ImGui::EndTabItem();
        }
        ImGui::EndTabBar();
    }
    ImGui::End();
}
bool GUIFunctions::typeCheck() {
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
void GUIFunctions::resetVariables() {
    if (hard_reset) {
        file_name = "";
        save_file = "";
        frame_rate = 0;
        first_frame = 1;
        last_frame = 0;
        max_frame = 0;
        current_frame = 1;
        prev_frame = 0;
        compare_start = 0;
        video_length = 0.0;
        selection = false;
        viewer_center_offset = 0;
        viewer_width = 0;  // TODO: Replace
        viewer_height = 0; // TODO: Replace
        show_imgui_metrics = false;
        show_imgui_demo = false;
        show_implot_metrics = false;
        show_implot_demo = false;
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
        show_viewer = false;
        disable_all = true;
        render_rect = false;
        click_in_rect = false;
        show_results = false;
        selection_warn = false;
        selected_algo = 0;
        frames.clear();
        hard_reset = false;
    }
    // texture //TODO: Clear
    // frame //TODO: Clear
    // sub_image //TODO: Clear
    // viewer_start_pos
    // viewer_size
    // selection_start_pos
    // selection_end_pos
    // viewport_center
    // window // ignore
    results.clear();
    peak_indexes.clear();
    cycle_times.clear();
    cycle_mean = 0;
    cycle_var = 0;
    cycle_stdev = 0;
}
void GUIFunctions::showMenuBar() {
    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("File")) {
            if (ImGui::MenuItem("Open", nullptr)) {
                // Reset all loader variables when loading a new video
                hard_reset = true;
                resetVariables();

                // Get a video file directory/name------------------------------
                char const* lTheOpenFileName;
                // Limit file types
                char const* lFilterPatterns[3] = {"*.mp4", "*.avi", "*.mov"};
                // Create open dialog
                lTheOpenFileName = tinyfd_openFileDialog(
                    "Select a Video File", (project_path.append("/")).c_str(),
                    3, lFilterPatterns, "Video files", 0);
                // Check if could open file
                if (!lTheOpenFileName) {
                    tinyfd_messageBox("Error", "File name is empty.", "ok",
                                      "error", 0);
                }
                // If file opens, make sure is right type and move on
                else {
                    file_name = lTheOpenFileName;
                    if (typeCheck()) {
                        right_type = true;
                    }
                    // Set flag to show the load dialog
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

    // Check for debug menu actions
    // TODO: Consider moving into if statements above
    if (show_imgui_demo)
        ImGui::ShowDemoWindow(&show_imgui_demo);
    if (show_implot_demo)
        ImPlot::ShowDemoWindow(&show_implot_demo);
    if (show_imgui_metrics)
        ImGui::ShowMetricsWindow(&show_imgui_metrics);
    if (show_implot_metrics)
        ImPlot::ShowMetricsWindow(&show_implot_metrics);
}
void GUIFunctions::loadFile() {
    if (show_load_dialog) {
        // Check if should show the error message
        if (show_load_error) {
            ImGui::OpenPopup("Error:");
            ImGui::SetNextWindowPos(viewport_center, ImGuiCond_Appearing,
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
        // Attempt to load the file to get info about it
        if (!skip_load_file) {
            // Create video loader
            cv::VideoCapture frame_loader(file_name);
            // If file is right type and can open,
            if (right_type && frame_loader.isOpened()) {
                // Load it once to get the size and properties
                if (!skip_get_size) {
                    frame_rate = frame_loader.get(cv::CAP_PROP_FPS);
                    while (true) {
                        frame_loader >> frame;
                        if (frame.empty())
                            break;
                        frame.release();
                        last_frame++;
                    }
                    // Set video length to other var to use last_frame later
                    max_frame = last_frame;
                    // Don't load like this again
                    skip_get_size = true;
                    // Show the next loading dialog
                    show_video_size = true;
                }
                // Show user the size of the video they're going to load
                if (show_video_size) {
                    // Create a centered pop-up window
                    ImGui::OpenPopup("Video File Info:");
                    ImGui::SetNextWindowPos(viewport_center,
                                            ImGuiCond_Appearing,
                                            ImVec2(0.5f, 0.5f));
                    // Show video properties
                    if (ImGui::BeginPopupModal(
                            "Video File Info:", NULL,
                            ImGuiWindowFlags_AlwaysAutoResize)) {
                        video_length = max_frame / frame_rate;
                        ImGui::Text(
                            "The selected file contains %d frames and is "
                            "%.02f seconds long.\n\nDo you want to load "
                            "the "
                            "entire file or just a portion?",
                            max_frame, video_length);
                        ImGui::Separator();
                        // Let user choose to load all or portion of video
                        // Predicts next dialog
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
                // If user chose to load whole file, do it
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
                    // Enable viewer
                    show_viewer = true;
                    disable_all = false;
                }
                // If user chose to load portion of video...
                if (load_portion) {
                    // Show a centered selection dialog
                    ImGui::OpenPopup("Select Frames:");
                    ImGui::SetNextWindowPos(viewport_center,
                                            ImGuiCond_Appearing,
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
                    // Load portion after selecting which frames
                    if (ready_load_portion) {
                        int loaded_frame_count = 0;
                        for (int i = 1; i <= last_frame; i++) {
                            frame_loader >> frame;
                            // Discard frames before user selected start frame
                            if (i < first_frame) {
                                frame.release();
                                continue;
                            }
                            // Stop loading when video frames are empty
                            if (frame.empty())
                                break;
                            frames.push_back(frame);
                            frame.release();
                            loaded_frame_count++;
                        }
                        max_frame = loaded_frame_count;
                        // TODO: ensure this next assignment was necessary
                        last_frame = max_frame;
                        load_portion = false;
                        // Enable viewer
                        show_viewer = true;
                        disable_all = false;
                    }
                }
            }
            // If loading failed, show error message
            else {
                show_load_error = true;
                skip_load_file = true;
            }
        }
    }
}
void GUIFunctions::saveFile(std::string out_file) {
    // reset save file for each time loading a new one
    // save_file = "";
    // get data file directory/name
    const char* lTheSaveFileName;
    // create a filter for file types
    char const* lFilterPatterns[1] = {"*.csv"};

    // local copy of project_path + file and ending
    std::string local_save_path = project_path;

    // create save dialog
    lTheSaveFileName = tinyfd_saveFileDialog(
        "Save Location?", (local_save_path.append(out_file)).c_str(), 1,
        lFilterPatterns, NULL);

    // check if not valid destination/name
    if (!lTheSaveFileName) {
        tinyfd_messageBox("Error", "Save file name is empty", "ok", "error",
                          1); // TODO: Make sure 1 or 0
    } else {
        save_file = lTheSaveFileName;
    }
}
void GUIFunctions::showViewer() {
    if (show_viewer) {
        // If we don't have a texture, make it, otherwise just show it.
        if (current_frame != prev_frame) {
            glGenTextures(1, &texture);
            glBindTexture(GL_TEXTURE_2D, texture);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                         frames[current_frame - 1].cols,
                         frames[current_frame - 1].rows, 0, GL_BGR,
                         GL_UNSIGNED_BYTE, frames[current_frame - 1].data);
            prev_frame = current_frame;
        }
        // Get size of where video will be drawn
        viewer_start_pos = ImGui::GetCursorScreenPos();
        ImVec2 window_max = ImGui::GetContentRegionAvail();

        // Find a max frame viewer size that honors video aspect ratio
        if (viewer_width == 0 || viewer_height == 0) {
            int frame_width = frames[current_frame - 1].cols;
            int frame_height = frames[current_frame - 1].rows;
            float aspect_ratio = (float)frame_width / (float)frame_height;
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
        viewer_center_offset =
            (window_max.x - viewer_start_pos.x - viewer_width) / 2;
        ImGui::GetWindowDrawList()->AddImage(
            (void*)(intptr_t)texture,
            ImVec2((viewer_start_pos.x + viewer_center_offset),
                   viewer_start_pos.y),
            ImVec2((viewer_start_pos.x + viewer_center_offset + viewer_width),
                   viewer_start_pos.y + viewer_height),
            ImVec2(0, 0), ImVec2(1, 1));
        if (selection == false) {
            selection_start_pos =
                ImVec2((viewer_start_pos.x + viewer_center_offset),
                       viewer_start_pos.y);
            selection_end_pos = ImVec2(
                (viewer_start_pos.x + viewer_center_offset + viewer_width),
                viewer_start_pos.y + viewer_height);
            render_rect = true;
            selection = true;
        }
        if (render_rect) {
            ImGui::GetWindowDrawList()->AddRect(
                selection_start_pos, selection_end_pos,
                ImGui::GetColorU32(IM_COL32(0, 130, 216, 255)), 0.0f, 0, 2.0f);
        }
        if (ImGui::IsMouseHoveringRect(
                ImVec2((viewer_start_pos.x + viewer_center_offset),
                       viewer_start_pos.y),
                ImVec2((viewer_width + viewer_center_offset), viewer_height),
                false)) {
            if (ImGui::IsMouseClicked(ImGuiMouseButton_Left)) {
                selection_start_pos = ImGui::GetMousePos();
                click_in_rect = true;
                render_rect = false;
            }
            if (click_in_rect == true
                && ImGui::IsMouseReleased(ImGuiMouseButton_Left)) {
                selection_end_pos = ImGui::GetMousePos();
                click_in_rect = false;
                render_rect = true;
            }
        }
    }
}
void GUIFunctions::selectionWarn() {
    if (selection_warn) {
        ImGui::OpenPopup("Error: No selection!");
        ImGui::SetNextWindowPos(viewport_center, ImGuiCond_Appearing,
                                ImVec2(0.5f, 0.5f));
        if (ImGui::BeginPopupModal("Error: No selection!", NULL,
                                   ImGuiWindowFlags_AlwaysAutoResize)) {
            ImGui::Text("Please select a portion of the video to "
                        "compare.\nThis software is meant to compare a region "
                        "of the video frame.\nIt is unlikely you will get good "
                        "results comparing whole frames.\nTo do it anyway, "
                        "select a large region of the frame.");
            ImGui::Separator();
            // ImGui::PopStyleVar();
            if (ImGui::Button("OK", ImVec2(120, 0))) {
                selection_warn = false;
                ImGui::CloseCurrentPopup();
            }
            ImGui::EndPopup();
        }
    }
}
void GUIFunctions::runComparison(float (*values_getter)(void* data, int idx,
                                                        cv::Mat* m,
                                                        cv::Mat* c)) {
    // Get selection region scaled correctly to compare against original frames
    float scale_factor = (float)frames[0].cols / (float)viewer_width;
    // normalize values of frame's region to be upper left to bottom right
    // regardless of how the user selected, e.g. bottom right to top left
    // TODO: simplify these calculations later..
    int row_start, row_end, col_start, col_end;
    if (selection_end_pos.y < selection_start_pos.y) {
        row_start = selection_end_pos.y;
        row_end = selection_start_pos.y;
    } else {
        row_start = selection_start_pos.y;
        row_end = selection_end_pos.y;
    }
    if (selection_end_pos.x < selection_start_pos.x) {
        col_start = selection_end_pos.x;
        col_end = selection_start_pos.x;
    } else {
        col_start = selection_start_pos.x;
        col_end = selection_end_pos.x;
    }
    // remove offset from centered viewer position
    row_start = row_start - viewer_start_pos.y;
    row_end = row_end - viewer_start_pos.y;
    col_start = col_start - viewer_start_pos.x - viewer_center_offset;
    col_end = col_end - viewer_start_pos.x - viewer_center_offset;
    // then scale up to real resolution
    row_start = row_start * scale_factor;
    row_end = row_end * scale_factor;
    col_start = col_start * scale_factor;
    col_end = col_end * scale_factor;

    // then do the opencv crop
    cv::Range rows(row_start, row_end);
    cv::Range cols(col_start, col_end);
    sub_image = frames[compare_start](rows, cols);

    // convert the sub image to hsv for comparison
    cv::Mat hsv_sub_image;
    cvtColor(sub_image, hsv_sub_image, cv::COLOR_BGR2HSV);

    // run the frame comparison for the selected algorithm
    for (int i = compare_start; i < last_frame; i++) {
        // create the comparison image
        cv::Mat compare_image = frames[i](rows, cols);
        // convert to hsv
        cv::Mat hsv_compare_image;
        cvtColor(compare_image, hsv_compare_image, cv::COLOR_BGR2HSV);
        // run comparison
        const float v =
            values_getter(nullptr, i, &hsv_sub_image, &hsv_compare_image);
        results.push_back(v);
        // release image data before next loop to ensure no overlap
        compare_image.release();
        hsv_compare_image.release();
    }
    normalizeResults();
}

void GUIFunctions::normalizeResults() {
    // TODO: Extend this to include the case of extended peaks + l/r
    // TODO: Decide what to do about constants, adjustable or not?
    // find the frame indexes of the cycles
    for (int i = 0; i < results.size(); i++) {
        if (selected_algo == 0 && results[i] > 0.95
            && (results[i] > results[i - 1] && results[i] > results[i + 1])) {
            peak_indexes.push_back(i);
        } else if (selected_algo == 1 && results[i] > 20.0
                   && (results[i] > results[i - 1]
                       && results[i] > results[i + 1])) {
            peak_indexes.push_back(i);
        } else if (selected_algo == 2 && results[i] < 5.0
                   && (results[i] < results[i - 1]
                       && results[i] < results[i + 1])) {
            if (results[i] < results[i - 2] && results[i] < results[i + 2]) {
                peak_indexes.push_back(i);
            }
        } else if (selected_algo == 3 && results[i] < 0.2
                   && (results[i] < results[i - 1]
                       && results[i] < results[i + 1])) {
            if (results[i] < results[i - 2] && results[i] < results[i + 2]) {
                peak_indexes.push_back(i);
            }
        }
    }
    for (int i = 0; i < peak_indexes.size() - 1; i++) {
        cycle_times.push_back((peak_indexes[i + 1] - peak_indexes[i])
                              / frame_rate);
        cycle_mean += cycle_times[i];
        // std::cout << peak_indexes[i] + current_frame << std::endl;
        // std::cout << cycle_times[i] << std::endl;
    }
    // std::cout << "cycle times: " << cycle_times.size() << std::endl;
    cycle_mean = cycle_mean / cycle_times.size();
    // std::cout << "cycle mean: " << cycle_mean << std::endl;
    double numerator = 0;
    for (int i = 0; i < cycle_times.size(); i++) {
        numerator += pow(cycle_times[i] - cycle_mean, 2);
    }
    cycle_var = numerator / (cycle_times.size() - 1);
    // std::cout << "cycle var: " << cycle_var << std::endl;
    cycle_stdev = sqrt(cycle_var);
    // std::cout << "cycle stdev: " << cycle_stdev << std::endl;

    show_results = true;
}
} // namespace oct
