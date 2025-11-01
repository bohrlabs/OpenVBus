#include "panel_bus_list.h"
#include <imgui.h>

using namespace ovb;
using namespace ovb::ui;

void panels::BusList(Context &ctx) {
    ImGui::Begin("Buses");
    if (ImGui::Button("+ New Bus"))
        ctx.m.newBus("Bus" + std::to_string(ctx.s.buses.size() + 1));
    ImGui::Separator();
    for (auto &b : ctx.s.buses) {
        bool selected = (ctx.s.selected_bus == b.id);
        if (ImGui::Selectable((b.name + "##" + std::to_string(b.id)).c_str(), selected))
            ctx.s.selected_bus = b.id;
    }
    ImGui::End();
}