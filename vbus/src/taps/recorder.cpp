
#include "recorder.h"
#include <cstring>

namespace vbus {

    bool Recorder::Open(const std::filesystem::path &path) {
        m_Out.open(path, std::ios::binary);
        if (!m_Out)
            return false;
        VCapHeader hdr{};
        std::memcpy(hdr.Magic, "VBUSCAP", 7);
        hdr.Version = 1;
        m_Out.write(reinterpret_cast<const char *>(&hdr), sizeof(hdr));
        return !!m_Out;
    }

    void Recorder::Close() {
        if (m_Out)
            m_Out.close();
    }

    bool Recorder::Write(const Frame &frame) {
        if (!m_Out)
            return false;
        VCapRec r{};
        r.Proto = static_cast<uint8_t>(frame.Proto);
        r.Flags = 0;
        r.Tag   = frame.Tag;
        r.Ts_ns = frame.Ts_ns;
        r.Len   = static_cast<uint32_t>(frame.Payload.size());
        m_Out.write(reinterpret_cast<const char *>(&r), sizeof(r));
        if (r.Len)
            m_Out.write(reinterpret_cast<const char *>(frame.Payload.data()), r.Len);
        return !!m_Out;
    }

    bool Replayer::Open(const fs::path &path) {
        m_In.open(path, std::ios::binary);
        if (!m_In)
            return false;
        VCapHeader hdr{};
        m_In.read(reinterpret_cast<char *>(&hdr), sizeof(hdr));
        if (!m_In)
            return false;
        if (std::memcmp(hdr.Magic, "VBUSCAP", 7) != 0)
            return false;
        if (hdr.Version != 1)
            return false;
        return true;
    }

    bool Replayer::Next(Frame &f_out) {
        if (!m_In)
            return false;
        VCapRec r{};
        m_In.read(reinterpret_cast<char *>(&r), sizeof(r));
        if (!m_In)
            return false;
        f_out.Proto = static_cast<Proto>(r.Proto);
        f_out.Tag   = r.Tag;
        f_out.Ts_ns = r.Ts_ns;
        f_out.Payload.resize(r.Len);
        if (r.Len)
            m_In.read(reinterpret_cast<char *>(f_out.Payload.data()), r.Len);
        return !!m_In;
    }

} // namespace vbus
