#include "../../include/Opaque.h"
#include "../core/Opaque.h"

/**
* Mètodes auxiliars per al wrapper de C
* */

struct OpaqueHandle {
    Opaque instance;
};

extern "C" {
    //CORE API
    OPAQUELIB_API OpaqueHandle *Opaque_Create() { return new OpaqueHandle(); }
    OPAQUELIB_API void Opaque_Destroy(OpaqueHandle *h) { delete h; }
    OPAQUELIB_API int Opaque_Suma(OpaqueHandle *h, int a, int b) {
        return (h)? h->instance.suma(a, b) : 0;
    }
}
