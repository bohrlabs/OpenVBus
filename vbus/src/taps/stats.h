
#pragma once
#include <atomic>
#include <cstdint>

namespace vbus {

    struct BusStats {
        std::atomic<uint64_t> Rx_frames{0};
        std::atomic<uint64_t> Tx_frames{0};
        std::atomic<uint64_t> Drops{0};
    };

} // namespace vbus
