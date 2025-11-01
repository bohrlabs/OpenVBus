#pragma once
#include <string>
#include <vector>
#include <cstdint>
#include <optional>
#include <deque>
#include <array>
#include "util/id_gen.h"

namespace ovb {

    struct Packet {
        uint64_t                timestamp_ns{};
        uint32_t                vlan{}; // 0 if none
        uint16_t                size{};
        std::array<uint8_t, 64> preview{}; // first bytes
    };

    struct FilterRule {
        enum class Type { Include,
            Exclude } type{Type::Include};
        std::string expr; // simple glob or BPF-like stub
    };

    struct InterfaceDesc {
        std::string name; // user friendly
        std::string driver; // mock, pcap, custom
    };

    struct Bus {
        uint32_t                     id{};
        std::string                  name;
        std::optional<InterfaceDesc> iface; // attached physical
        std::vector<FilterRule>      filters;
        std::deque<Packet>           ring; // recent packets
        bool                         enabled{true};
    };

    struct AppState {
        std::vector<Bus> buses;
        uint32_t         selected_bus{};
        bool             show_demo{false};
    };

} // namespace ovb