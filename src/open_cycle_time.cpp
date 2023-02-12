#include "open_cycle_time.h"

namespace oct {
OpenCycleTime::OpenCycleTime(const std::string& window_title,
                             unsigned short width, unsigned short height)
    : context{window_title, width, height} {}
OpenCycleTime::~OpenCycleTime() {}
void OpenCycleTime::loop() {
    context.loop();
}
bool OpenCycleTime::isActive() const {
    return context.isActive();
}
} // namespace oct
