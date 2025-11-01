#include "model.h"
#include "util/id_gen.h"
#include <algorithm>
#include <cstring>

using namespace ovb;

Model::Model(AppState &s)
    : state(s) {}

Bus &Model::newBus(const std::string &name) {
    Bus b;
    b.id   = ovb::next_id();
    b.name = name;
    state.buses.push_back(std::move(b));
    state.selected_bus = state.buses.back().id;
    return state.buses.back();
}

void Model::deleteBus(uint32_t id) {
    state.buses.erase(std::remove_if(state.buses.begin(), state.buses.end(),
                          [&](const Bus &b) { return b.id == id; }),
        state.buses.end());
    if (!state.buses.empty())
        state.selected_bus = state.buses.front().id;
}

Bus *Model::getBus(uint32_t id) {
    for (auto &b : state.buses)
        if (b.id == id)
            return &b;
    return nullptr;
}

void Model::tick(double dt) {
    // mock packets for enabled buses
    std::uniform_int_distribution<int> sizeDist(64, 1500);
    std::uniform_int_distribution<int> vlanDist(0, 1);
    for (auto &b : state.buses) {
        if (!b.enabled)
            continue;
        Packet p;
        p.timestamp_ns += static_cast<uint64_t>(dt * 1e9);
        p.vlan = vlanDist(rng) ? 100 : 0;
        p.size = static_cast<uint16_t>(sizeDist(rng));
        for (int i = 0; i < 64; i++) p.preview[i] = static_cast<uint8_t>(rng());
        b.ring.push_front(p);
        if (b.ring.size() > 4096)
            b.ring.pop_back();
    }
}

std::vector<InterfaceDesc> Model::enumerateIfaces() const {
    std::vector<InterfaceDesc> out;
    out.push_back({"Mock NIC", "mock"});
#ifdef OPENVBUS_WITH_PCAP
    out.push_back({"PCAP: Select at runtime", "pcap"});
#endif
    return out;
}