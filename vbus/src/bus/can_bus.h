
#pragma once
#include "ibus.h"
#include <mutex>
#include "../core/scheduler.h"
namespace vbus {

    class CanBus: public IBus {
      public:
        CanBus(Scheduler &s, Clock &c, uint32_t bitrate);
        void Connect(IEndpoint *ep) override;
        void Disconnect(IEndpoint *ep) override;
        void Send(IEndpoint *src, Frame f) override;
        void SetRecordCb(std::function<void(const Frame &)> cb) {
            m_Rec_cb = std::move(cb);
        }

      private:
        Scheduler                         &M_Scheduler;
        Clock                             &m_Clock;
        EndpointList                       m_EndpointList;
        uint32_t                           m_Bitrate;
        std::function<void(const Frame &)> m_Rec_cb;
        std::mutex                         m_Mtx;
    };

} // namespace vbus
