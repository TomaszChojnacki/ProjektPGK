#pragma once

/// Includujemy niezbedne naglowki z biblioteki OGL3D
#include <OGL3D/OPrerequisites.h>

/// Klasa ORect reprezentuje prostokat w silniku graficznym
class ORect
{
public:
    /// Konstruktor domyslny klasy ORect
    ORect() {}

    /// Konstruktor klasy ORect przyjmuj¹cy szerokosc i wysokosc kwadratu
    ORect(i32 width, i32 height) : width(width), height(height) {}

    /// Konstruktor klasy ORect, przyjmujacy lewy, gorny rog, szerokosc i wysokosc kwadratu
    ORect(i32 left, i32 top, i32 width, i32 height) : left(left), top(top), width(width), height(height) {}

    /// Konstruktor kopiujacy klasy ORect
    ORect(const ORect& rect) : left(rect.left), top(rect.top), width(rect.width), height(rect.height) {}

public:
    /// Szerokosc i wysokosc kwadratu
    i32 width = 0, height = 0;

    /// Wspolrzedne lewego gornego rogu kwadratu
    i32 left = 0, top = 0;
};
