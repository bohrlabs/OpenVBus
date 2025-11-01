
#pragma once
#include "../core/clock.h"
#include "frame.h"

#include <vector>
#include <memory>
#include <functional>

namespace vbus {

    class IEndpoint {
      public:
        virtual ~IEndpoint()               = default;
        virtual void On_rx(const Frame &f) = 0;
    };

    class IBus {
      public:
        virtual ~IBus()                                = default;
        virtual void Connect(IEndpoint *ep)            = 0;
        virtual void Disconnect(IEndpoint *ep)         = 0;
        virtual void Send(IEndpoint *src, Frame frame) = 0;
    };

    using EndpointList = std::vector<IEndpoint *>;

} // namespace vbus
