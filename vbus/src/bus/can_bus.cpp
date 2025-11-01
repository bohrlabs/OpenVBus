
#include "can_bus.h"
#include <algorithm>

namespace vbus {

    CanBus::CanBus(Scheduler &s, Clock &c, uint32_t br)
        : M_Scheduler(s), m_Clock(c), m_Bitrate(br) {}

    void CanBus::Connect(IEndpoint *ep) {
        std::scoped_lock lk(m_Mtx);
        m_EndpointList.push_back(ep);
    }

    void CanBus::Disconnect(IEndpoint *ep) {
        std::scoped_lock lk(m_Mtx);
        m_EndpointList.erase(std::remove(m_EndpointList.begin(), m_EndpointList.end(), ep), m_EndpointList.end());
    }

    void CanBus::Send(IEndpoint *src, Frame f) {
        // MVP: immediate broadcast. TODO: proper arbitration and timing.
        f.Proto = Proto::CAN20;
        f.Ts_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(m_Clock.Now()).count();
        if (m_Rec_cb)
            m_Rec_cb(f);
        std::scoped_lock lk(m_Mtx);
        for (auto *ep : m_EndpointList)
            if (ep != src)
                ep->On_rx(f);
    }

} // namespace vbus
