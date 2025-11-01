
#pragma once

#include "bus/frame.h"
#include "core/core.h"

#include <fstream>

namespace vbus {

    struct VCapHeader {
        char     Magic[8]; // "VBUSCAP"
        uint32_t Version; // 1
        uint32_t Reserved;
    };

    struct VCapRec {
        uint8_t  Proto; // matches Proto
        uint8_t  Flags; // reserved
        uint16_t Reserved;
        uint64_t Tag; // CAN id, or 0
        uint64_t Ts_ns; // timestamp
        uint32_t Len; // payload bytes
    };

    class Recorder {
      public:
        bool Open(const fs::path &path);
        void Close();
        bool Write(const Frame &frame);

      private:
        std::ofstream m_Out;
    };

    class Replayer {
      public:
        enum class Mode {
            Exact,
            Burst,
            Scale
        };
        bool Open(const fs::path &path);
        bool Next(Frame &f_out);

      private:
        std::ifstream m_In;
    };

} // namespace vbus
