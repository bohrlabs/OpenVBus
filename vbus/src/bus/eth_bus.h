
#pragma once
#include "ibus.h"
#include <mutex>
#include "../core/scheduler.h"
namespace vbus {

    class EthHub: public IBus {
      public:
        EthHub(Scheduler &s, Clock &c, uint64_t link_bps);
        void Connect(IEndpoint *ep) override;
        void Disconnect(IEndpoint *ep) override;
        void Send(IEndpoint *src, Frame f) override;
        void SetRecordCb(std::function<void(const Frame &)> cb) {
            m_Rec_cb = std::move(cb);
        }

      private:
        Scheduler                         &m_Scheduler;
        Clock                             &m_Clock;
        EndpointList                       m_EndpointList;
        uint64_t                           m_Link_bps;
        std::function<void(const Frame &)> m_Rec_cb;
        std::mutex                         m_Mtx;
    };

} // namespace vbus
