
#pragma once
#include <chrono>

namespace vbus {

    using SimTime = std::chrono::nanoseconds;

    struct Clock {
        virtual ~Clock()            = default;
        virtual SimTime Now() const = 0;
    };

    struct RealtimeClock final: Clock {
        SimTime Now() const override {
            using clock          = std::chrono::steady_clock;
            static const auto t0 = clock::now();
            auto              dt = clock::now() - t0;
            return std::chrono::duration_cast<SimTime>(dt);
        }
    };

} // namespace vbus
