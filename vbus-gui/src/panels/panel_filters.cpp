#include "panel_filters.h"
#include <imgui.h>

using namespace ovb;
using namespace ovb::ui;

void panels::Filters(Context &ctx) {
    ImGui::Begin("Filters");
    auto *bus = ctx.m.getBus(ctx.s.selected_bus);
    if (!bus) {
        ImGui::TextUnformatted("No bus selected");
        ImGui::End();
        return;
    }

    if (ImGui::Button("+ Include"))
        bus->filters.push_back({ovb::FilterRule::Type::Include, "vlan==100"});
    ImGui::SameLine();
    if (ImGui::Button("+ Exclude"))
        bus->filters.push_back({ovb::FilterRule::Type::Exclude, "size>1400"});

    for (size_t i = 0; i < bus->filters.size(); ++i) {
        auto &f = bus->filters[i];
        ImGui::PushID((int)i);
        int t = (f.type == ovb::FilterRule::Type::Include) ? 0 : 1;
        ImGui::Combo("Type", &t, "Include\0Exclude\0");
        f.type = t ? ovb::FilterRule::Type::Exclude : ovb::FilterRule::Type::Include;
        ImGui::InputText("Expr", f.expr.data(), f.expr.capacity() + 1);
        if (ImGui::Button("Delete")) {
            bus->filters.erase(bus->filters.begin() + i);
            ImGui::PopID();
            break;
        }
        ImGui::Separator();
        ImGui::PopID();
    }

    ImGui::End();
}