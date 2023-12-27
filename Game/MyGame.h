#pragma once

/// Includujemy wszystkie niezbedne naglowki z include OGL3D
#include <OGL3D/All.h>

/// Includujemy naglowek klasy MyPlayer, ktora reprezentuje gracza w silniku
#include "MyPlayer.h"

/// Klasa MyGame dziedziczy publicznie po klasie OGame
class MyGame : public OGame
{
public:
    /// Konstruktor klasy MyGame
    MyGame();

    /// Destruktor klasy MyGame
    ~MyGame();

    /// Metoda wywolywana podczas tworzenia instancji gry
    virtual void onCreate();

    /// Metoda wywolywana podczas aktualizacji stanu gry
    virtual void onUpdate(f32 deltaTime);

private:
    /// Zmienna przechowujaca uplywajacy czas od rozpoczecia gry
    f32 m_elapsedSeconds = 0.0f;

    /// Wskaznik na obiekt klasy MyPlayer reprezentujacy gracza w grze
    MyPlayer* m_player = nullptr;
};
