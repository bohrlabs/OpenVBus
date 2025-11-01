#pragma once
#include <string>
#include <vector>
#include "app_state.h"
#include <memory>
namespace ovb::iface {

    struct Stats {
        uint64_t rx_pkts{}, tx_pkts{};
    };

    class Base {
      public:
        virtual ~Base()                   = default;
        virtual const char *name() const  = 0;
        virtual bool        start()       = 0;
        virtual void        stop()        = 0;
        virtual Stats       stats() const = 0;
    };

    std::unique_ptr<Base> make(const InterfaceDesc &desc);

} // namespace ovb::iface