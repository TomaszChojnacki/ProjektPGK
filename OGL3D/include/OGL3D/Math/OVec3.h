#pragma once

/// Includujemy niezbedne naglowki z biblioteki OGL3D
#include <OGL3D/OPrerequisites.h>

/// Klasa OVec3 reprezentuje trojwymiarowy wektor w silniku graficznym
class OVec3
{
public:
    /// Konstruktor domyslny klasy OVec3
    OVec3() {}

    /// Konstruktor klasy OVec3 przyjmuj¹cy wspolrzedne x, y i z
    OVec3(f32 x, f32 y, f32 z) : x(x), y(y), z(z) {}

public:
    /// Wspolrzedna x wektora
    f32 x = 0;

    /// Wspolrzedna y wektora
    f32 y = 0;

    /// Wspolrzedna z wektora
    f32 z = 0;
};
