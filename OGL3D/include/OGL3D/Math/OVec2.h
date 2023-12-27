#pragma once

/// Includujemy niezbedne naglowki z biblioteki OGL3D
#include <OGL3D/OPrerequisites.h>

/// Klasa OVec2 reprezentuje dwuwymiarowy wektor w silniku graficznym
class OVec2
{
public:
    /// Konstruktor domyslny klasy OVec2
    OVec2() {}

    /// Konstruktor klasy OVec2 przyjmujacy wspolrzedne x i y
    OVec2(f32 x, f32 y) : x(x), y(y) {}

public:
    /// Wspolrzedna x wektora
    f32 x = 0;

    /// Wspolrzedna y wektora
    f32 y = 0;
};
