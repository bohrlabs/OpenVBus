
#define VBUS_CLIENT_EXPORTS
#include "vbus_client.h"
#include <windows.h>

struct VBusHandle {
    void* reserved{};
};

extern "C" {

VBUS_API VBusHandle* vbus_open(const wchar_t* busName) {
    (void)busName;
    // TODO: Map shared memory for busName
    return new VBusHandle{};
}

VBUS_API void vbus_close(VBusHandle* h) {
    delete h;
}

} // extern "C"
