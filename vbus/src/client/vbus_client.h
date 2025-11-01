
#pragma once
// Placeholder C API for future shared-memory data plane.
// For now, clients should interact via the control pipe or link into vbus_core directly for tests.

#ifdef _WIN32
#  ifdef VBUS_CLIENT_EXPORTS
#    define VBUS_API __declspec(dllexport)
#  else
#    define VBUS_API __declspec(dllimport)
#  endif
#else
#  define VBUS_API
#endif

#include <cstdint>
#include <cstddef>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct VBusHandle VBusHandle;

VBUS_API VBusHandle* vbus_open(const wchar_t* busName);
VBUS_API void        vbus_close(VBusHandle* h);

// TODO: implement shared memory ring reader/writer in a future step.

#ifdef __cplusplus
}
#endif
