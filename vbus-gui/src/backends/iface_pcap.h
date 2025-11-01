#pragma once
#ifdef OPENVBUS_WITH_PCAP
    #include "iface_base.h"
    #include <pcap/pcap.h>

namespace ovb::iface {
    class PCap: public Base {
        pcap_t       *handle = nullptr;
        mutable Stats s{};

      public:
        const char *name() const override {
            return "PCAP";
        }
        bool  start() override;
        void  stop() override;
        Stats stats() const override {
            return s;
        }
    };
    std::unique_ptr<Base> make_pcap();
} // namespace ovb::iface
#endif
