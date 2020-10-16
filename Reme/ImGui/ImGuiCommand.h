#pragma once

#include <Reme/Events/Event.h>

namespace Reme {
class ImGuiCommand {
public:
    static void initialize();
    static void shutdown();

    static void begin();
    static void end();

    static bool should_swallow_event(Event& event);
};
} // namespace Reme
