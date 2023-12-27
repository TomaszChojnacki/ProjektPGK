#pragma once

/// Includujemy niezbedne naglowki z biblioteki OGL3D
#include <OGL3D/OPrerequisites.h>

/// Klasa OVec4 reprezentuje czterowymiarowy wektor w silniku graficznym
class OVec4
{
public:
    /// Konstruktor domyslny klasy OVec4
    OVec4() {}

    /// Konstruktor klasy OVec4 przyjmujacy wspolrzedne x, y, z i w
    OVec4(f32 x, f32 y, f32 z, f32 w) : x(x), y(y), z(z), w(w) {}

public:
    /// Wspolrzedna x wektora
    f32 x = 0;

    /// Wspolrzedna y wektora
    f32 y = 0;

    /// Wspolrzedna z wektora
    f32 z = 0;

    /// Wspolrzedna w wektora
    f32 w = 0;
};
