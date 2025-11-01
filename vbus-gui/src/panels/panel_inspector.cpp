#include "panel_inspector.h"
#include <imgui.h>

using namespace ovb;
using namespace ovb::ui;

void panels::Inspector(Context &ctx) {
    ImGui::Begin("Inspector");
    auto *bus = ctx.m.getBus(ctx.s.selected_bus);
    if (!bus) {
        ImGui::TextUnformatted("No bus selected");
        ImGui::End();
        return;
    }

    ImGui::InputText("Name", bus->name.data(), bus->name.capacity() + 1);
    ImGui::Checkbox("Enabled", &bus->enabled);

    if (ImGui::CollapsingHeader("Interface", ImGuiTreeNodeFlags_DefaultOpen)) {
        if (!bus->iface) {
            if (ImGui::Button("Attach"))
                ImGui::OpenPopup("iface_popup");
        } else {
            ImGui::Text("%s (%s)", bus->iface->name.c_str(), bus->iface->driver.c_str());
            if (ImGui::Button("Detach"))
                bus->iface.reset();
        }
        if (ImGui::BeginPopup("iface_popup")) {
            for (auto &d : ctx.m.enumerateIfaces()) {
                if (ImGui::Selectable((d.name + " [" + d.driver + "]").c_str()))
                    bus->iface = d;
            }
            ImGui::EndPopup();
        }
    }

    ImGui::End();
}