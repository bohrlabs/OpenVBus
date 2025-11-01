#pragma once
#include "iface_base.h"
#include <random>

namespace ovb::iface {
    class Mock: public Base {
        mutable Stats   s{};
        std::mt19937_64 rng{42};
        bool            running = false;

      public:
        const char *name() const override {
            return "Mock";
        }
        bool start() override {
            running = true;
            return true;
        }
        void stop() override {
            running = false;
        }
        Stats stats() const override {
            return s;
        }
    };
} // namespace ovb::iface