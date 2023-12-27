#pragma once

/// Includujemy niezbedne naglowki z biblioteki OGL3D
#include <OGL3D/Math/ORect.h>

/// Klasa OWindow reprezentuje okno w silniku graficznym
class OWindow
{
public:
    /// Konstruktor klasy OWindow
    OWindow();

    /// Destruktor klasy OWindow
    ~OWindow();

    /// Metoda zwracajaca rozmiar wewnetrzny okna
    ORect getInnerSize();

    /// Metoda ustawiajaca biezacy kontekst okna
    void makeCurrentContext();

    /// Metoda prezentujaca okno z opcja wlaczenia lub wylaczenia synchronizacji pionowej (vsync)
    void present(bool vsync);

private:
    /// Wskaznik do uchwytu okna
    void* m_handle = nullptr;

    /// Wskaznik do kontekstu okna
    void* m_context = nullptr;
};
