#include "iface_mock.h"
#include "iface_base.h"
#include <memory>

using namespace ovb::iface;

std::unique_ptr<Base> ovb::iface::make(const ovb::InterfaceDesc &d) {
    if (d.driver == "mock")
        return std::make_unique<Mock>();
#ifdef OPENVBUS_WITH_PCAP
    extern std::unique_ptr<Base> make_pcap();
    if (d.driver == "pcap")
        return make_pcap();
#endif
    return {};
}

