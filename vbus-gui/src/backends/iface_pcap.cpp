#ifdef OPENVBUS_WITH_PCAP
    #include "iface_pcap.h"
    #include <memory>

using namespace ovb::iface;

bool PCap::start() {
    return false;
}
void                  PCap::stop() {}
std::unique_ptr<Base> make_pcap() {
    return std::make_unique<PCap>();
}
#endif

