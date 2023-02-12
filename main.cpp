#include "open_cycle_time.h"

int main() {
    oct::OpenCycleTime open_cycle_time("Open Cycle Time", 640, 480);
    while (open_cycle_time.isActive()) {
        open_cycle_time.loop();
    }
    return 0;
}
