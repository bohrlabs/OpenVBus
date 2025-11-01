#include "panel_vlan.h"
#include <imgui.h>

using namespace ovb;
using namespace ovb::ui;

void panels::VLAN(Context &ctx) {
    ImGui::Begin("VLAN Manager");
    auto *bus = ctx.m.getBus(ctx.s.selected_bus);
    if (!bus) {
        ImGui::TextUnformatted("No bus selected");
        ImGui::End();
        return;
    }
    static int vlan = 100;
    ImGui::InputInt("Default VLAN", &vlan);
    ImGui::Text("Attach policies coming soon");
    ImGui::End();
}