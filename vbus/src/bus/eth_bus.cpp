
#include "eth_bus.h"
#include <algorithm>

namespace vbus {

    EthHub::EthHub(Scheduler &s, Clock &c, uint64_t bps)
        : m_Scheduler(s), m_Clock(c), m_Link_bps(bps) {}

    void EthHub::Connect(IEndpoint *ep) {
        std::scoped_lock lk(m_Mtx);
        m_EndpointList.push_back(ep);
    }

    void EthHub::Disconnect(IEndpoint *ep) {
        std::scoped_lock lk(m_Mtx);
        m_EndpointList.erase(std::remove(m_EndpointList.begin(), m_EndpointList.end(), ep), m_EndpointList.end());
    }

    void EthHub::Send(IEndpoint *src, Frame frame) {
        // MVP: immediate delivery. TODO: serialization delay using link_bps.
        frame.Proto = Proto::ETH2;
        frame.Ts_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(m_Clock.Now()).count();
        if (m_Rec_cb)
            m_Rec_cb(frame);
        std::scoped_lock lk(m_Mtx);
        for (auto *ep : m_EndpointList)
            if (ep != src)
                ep->On_rx(frame);
    }

} // namespace vbus
