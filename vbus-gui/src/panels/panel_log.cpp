#include "panel_log.h"
#include <imgui.h>

using namespace ovb;
using namespace ovb::ui;

void panels::Log(Context &) {
    ImGui::Begin("Log");
    ImGui::TextUnformatted("Startup OK");
    ImGui::End();
}