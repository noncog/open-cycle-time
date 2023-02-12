#pragma once
#ifndef OPEN_CYCLE_TIME_OPEN_CYCLE_TIME_H
#define OPEN_CYCLE_TIME_OPEN_CYCLE_TIME_H
#include "gui_context.h"
#include <string>

namespace oct {
class OpenCycleTime {
public:
    OpenCycleTime(const std::string& window_title, unsigned short width,
                  unsigned short height);
    ~OpenCycleTime();
    void loop();
    bool isActive() const;

private:
    oct::GUIContext context;
};

} // namespace oct

#endif // OPEN_CYCLE_TIME_OPEN_CYCLE_TIME_H
