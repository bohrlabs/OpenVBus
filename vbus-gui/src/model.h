#pragma once
#include "app_state.h"
#include <random>

namespace ovb {

    class Model {
      public:
        explicit Model(AppState &s);
        Bus                       &newBus(const std::string &name);
        void                       deleteBus(uint32_t id);
        Bus                       *getBus(uint32_t id);
        void                       tick(double dt);
        std::vector<InterfaceDesc> enumerateIfaces() const; // mock and pcap
      private:
        AppState       &state;
        std::mt19937_64 rng{1234};
    };

} // namespace ovb