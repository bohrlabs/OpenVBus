#pragma once
#include <atomic>
namespace ovb {
    inline uint32_t next_id() {
        static std::atomic_uint32_t x{1};
        return x++;
    }
} // namespace ovb