#include "panel_packets.h"
#include <imgui.h>

using namespace ovb;
using namespace ovb::ui;

static bool pass(const FilterRule &r, const Packet &p) {
    // placeholder evaluator: only checks vlan==100 or size>1400 cases
    if (r.expr.find("vlan==100") != std::string::npos) {
        bool m = (p.vlan == 100);
        return r.type == FilterRule::Type::Include ? m : !m;
    }
    if (r.expr.find("size>1400") != std::string::npos) {
        bool m = (p.size > 1400);
        return r.type == FilterRule::Type::Include ? m : !m;
    }
    return true;
}

void panels::Packets(Context &ctx) {
    ImGui::Begin("Packets");
    auto *bus = ctx.m.getBus(ctx.s.selected_bus);
    if (!bus) {
        ImGui::TextUnformatted("No bus selected");
        ImGui::End();
        return;
    }

    ImGui::Text("Recent: %zu", bus->ring.size());
    ImGui::Separator();
    ImGui::BeginChild("pktlist", ImVec2(0, 0), true);
    int idx = 0;
    for (const auto &p : bus->ring) {
        bool ok = true;
        for (const auto &f : bus->filters) ok &= pass(f, p);
        if (!ok)
            continue;
        ImGui::Text("%04d | t=%llu ns | vlan=%u | size=%u", idx++, (unsigned long long)p.timestamp_ns, p.vlan, p.size);
    }
    ImGui::EndChild();
    ImGui::End();
}