/**
* Wrapper de tipus Move-Only RAII
* */
#pragma once
#include "Opaque.h"

class Opaque {
public:
    //gestor estàndar de la classe exportada
    Opaque() : handle(Opaque_Create()) {}
    ~Opaque() { if(handle) Opaque_Destroy(handle); }
    Opaque(const Opaque&) = delete;
    Opaque& operator=(const Opaque&) = delete;
    Opaque(Opaque&& other) noexcept : handle(other.handle) { other.handle = nullptr; }
    Opaque& operator=(Opaque&& other) noexcept {
        if(this != &other) {
            Opaque_Destroy(handle);
            handle = other.handle;
            other.handle = nullptr;
        }
        return *this;
    }

    //mètodes exportats
    int suma(int a, int b) {return Opaque_Suma(handle, a, b); }

private:
    OpaqueHandle *handle;
};